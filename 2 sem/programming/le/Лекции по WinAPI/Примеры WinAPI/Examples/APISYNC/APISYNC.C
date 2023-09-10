/*************************************************************
Файл APISync.c
Copyright (c) 1996 Мешков А., Тихомиров Ю.
*************************************************************/

#include <windows.h>         /* описание функций Win32® API */

#define NUMBER_OF_THREADS	  10
#define NUMBER_OF_RESOURCES 10

/* массив для хранения имени модуля */
TCHAR szModuleName[_MAX_PATH]; 

/* массив для текстовых сообщений */
TCHAR szMessage[64*NUMBER_OF_THREADS];
TCHAR szMessageCode[64];

/* описатели событий и семафоров */
HANDLE hEmpty, hQuit, hResource;
/* объект критическая секция */
CRITICAL_SECTION section;
/* массив описателей потоков */
HANDLE hThread[NUMBER_OF_THREADS];
/* массив для хранения количества полученных ресурсов */
DWORD dwCount[NUMBER_OF_THREADS];

/* количество ресурсов */
DWORD dwResources = NUMBER_OF_RESOURCES;

/* описание потоковой функции */
DWORD ThreadFunc(LPVOID lParam);

/* главная функция приложения */
int WINAPI WinMain(HINSTANCE hInstance, 
                   HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, 
                   int nCmdShow)
{
  int i;
  DWORD dwWait, dwExit, dwThreadId;
  PROCESS_INFORMATION pi;
  STARTUPINFO si;

  /*
     проверяем не было ли запущена уже копия приложения
     будем использовать этот объект и для инициирования
     завершения потоков
  */
  hQuit = CreateEvent(
    NULL,        /* используем атрибуты защиты по умолчанию */
    TRUE,               /* создаем события с ручным сбросом */
    FALSE,                 /* начальное состояние - сброшен */
    "Abracadabra"                         /* уникальное имя */
    );

  /* если приложение запущено - 
     завершаем выполнение с кодом 1 */
  if (GetLastError() == ERROR_ALREADY_EXISTS)
    return (1);

  /*
     запускаем копию процесса 
  */

  /* заполняем структуру STARTUPINFO */
  GetStartupInfo(&si);

  /* получаем имя исполняемого модуля */
  GetModuleFileName(NULL, szModuleName, _MAX_PATH);

  /* создаем копию приложения */
  CreateProcess(
    NULL,	    /* имя модуля передадим во втором параметре */
    szModuleName,              /* командная строка процесса */
    NULL,                     /* используем атрибуты защиты 
                                      процесса по умолчанию */
    NULL, /* используем атрибуты защиты потока по умолчанию */
    FALSE,                      /* описатель не наследуемый */
    CREATE_DEFAULT_ERROR_MODE,      /* стандартая обработка 
                                                     ошибок */
    NULL,                  /* переменные окружения не нужны */
    NULL,                  /* текущий каталог не используем */
    &si,                      /* передаем копию собственной 
                                      структуры STARTUPINFO */
    &pi /* получим описатель и другую информацию о процессе */
    );

  /*
     процесс должен завершиться немедленно, 
     т.к. уже загружена его копия
  */

  /* ожидаем завершения дочернего процесса */
  dwWait = WaitForSingleObject(pi.hProcess, 5000);

  /*
     процесс должен завершиться немедленно, 
     т.к. уже загружена его копия
  */
  if (dwWait == WAIT_OBJECT_0)
  {
    GetExitCodeProcess(pi.hProcess, &dwExit);
    wsprintf(szMessage, 
      "Копия процесса завершена.\nКод завершения: %d",
      dwExit);
    MessageBox(NULL, szMessage, "APISync", MB_OK);
  }
  else if (dwWait == WAIT_TIMEOUT)
    MessageBox(NULL, "дочерний процесс не завершился"
      "по истечению 5 секунд", "APISync", MB_OK);
  else
    ;                       /* этот код никогда выполняется */

  /* объект используется для сигнализации 
     об исчерпывании ресурсов */
  hEmpty = CreateEvent(NULL, FALSE, FALSE, NULL);

  /* семафор для синхронизации доступа к ресурсам */
  hResource = CreateSemaphore(
    NULL,        /* используем атрибуты защиты по умолчанию */
    NUMBER_OF_RESOURCES,     /* начальное значение счетчика */
    NUMBER_OF_RESOURCES,  /* максимальное значение счетчика */
    NULL                       /* создаем объект безымянным */
    );

  /* инициализация критической секции для защиты переменной,
     содержащей количество свободных ресурсов */
  InitializeCriticalSection(&section);

  /* создаем все потоки */
  for (i = 0; i < NUMBER_OF_THREADS; i++)
    hThread[i] = CreateThread(
      NULL,      /* используем атрибуты защиты по умолчанию */
      0,                          /* начальный размер стека, 
                                  как и у создающего потока */
      (LPTHREAD_START_ROUTINE)ThreadFunc,      /* указатель 
                                          на функцию потока */
      &dwCount[i],         /* адрес переменной для хранения 
                             количества выделенных ресурсов */
      (i % 3) ? 0 : CREATE_SUSPENDED,      /* часть потоков
                                   создаем, но не запускаем */
      &dwThreadId    /* по завершению получим идентификатор
                           потока, хотя и не используем его
                                       идентификатор потока */
      );

  /* ждем момента, когда все ресурсы будут 
     исчерпаны или истекут 5 секунд */
  WaitForSingleObject(hEmpty, 5000);

  /* инициируем окончание потоков */
  PulseEvent(hQuit);

  /* ждем завершения потоков, но не более 5-ти секунд */
  WaitForMultipleObjects(
    NUMBER_OF_THREADS,       /* количество синхронизирующих 
                                                   объектов */
    hThread, /* массив описателей синхронизирующих объектов */
    TRUE,         /* ждем установки всех указанных объектов */
    5000                            /* но не более 5 секунд */
    );

  /* 
     формируем протокольное сообщение:
       - заголовок 
       - номер потока, код возврата и значение переменной, 
         хранящей количество выделенных потоку ресурсов 
         (должны быть равны - печатаем для проверки)
  */
  lstrcpy(szMessage, "Протокол завершения потоков.\n\n");

  for (i = 0; i < NUMBER_OF_THREADS; i++)
  {
    /* получаем код возврата, содержащий 
       количество выделенных потоку ресурсов */
    GetExitCodeThread(hThread[i], &dwExit);

    /* часть потоков могла не завершиться:
       одни потоки находились в приостановленном состоянии,
       другие в момент вызова функции PulseEvent 
       еще не вызвали в очередной раз ожидающую 
       функцию WaitForMultipleObjects - удаляем их */
    if (dwExit == STILL_ACTIVE)
    {
      /* насильно удаляем поток */
      TerminateThread(hThread[i], 0);

      if ((i % 3) == 0) /* такие потоки были приостановлены */
        wsprintf(szMessageCode, "\tПоток %d - удален\n", i);
      else
        wsprintf(szMessageCode, 
          "\tПоток %d - удален (ресурсов %d)\n", 
          i, dwCount[i]);
    }
    else
      wsprintf(szMessageCode, 
        "\tПоток %d - ресурсов %d (%d)\n", 
        i, dwExit, dwCount[i]);

    lstrcat(szMessage, szMessageCode);
  }

  wsprintf(szMessageCode, 
    "\nСвободных ресурсов %d\n", dwResources);

  lstrcat(szMessage, szMessageCode);

  MessageBox(NULL, szMessage, "APISync", MB_OK);

  /* удаляем синхронизирующие объекты */
  DeleteCriticalSection(&section);

  CloseHandle(hResource);
  CloseHandle(hQuit);

  /* нормальное завершение процесса */
  return (0);
}

/* 
   функция потока, ожидает освобождения ресурса или 
   сигнала о завершении, если потоку уже выделено пять и 
   более ресурсов - освобождаем все
*/
DWORD ThreadFunc(LPVOID lParam)
{
  DWORD dwWait;

  /* преобразуем параметр в указатель на переменную 
     для хранения количества выделенных потоку ресурсов */
  LPDWORD lpdwCount = (LPDWORD)lParam;

  /* 
     формируем массив синхронизирующих объектов:
       - событие для сигнализации о 
         необходимости завершения 
       - описатель семафора, синхронизирующего 
         выделение ресурсов 
  */
  HANDLE hHandle[] = { hQuit, hResource };

  *lpdwCount = 0;
  
  for (; ;)
  {
    dwWait = WaitForMultipleObjects(
      2,            /* количество синхронизирующих объектов */
      hHandle,                        /* массив описателей 
                                  синхронизирующих объектов */
      FALSE,            /* ждем установки хотя бы одного из
                                         указанных объектов */
      INFINITE                /* ограничения по времени нет */
    );

    if (dwWait == WAIT_OBJECT_0)      /* hQuit - установлен */
      break;
    else                                 /* получили ресурс */
    {
      if ((*lpdwCount + 1) >= 5)     /* освобождаем ресурсы */
      {
        /* здесь будем изменять переменную, содержащую 
           количество свабодных ресурсов */
        EnterCriticalSection(&section);

        /* увеличиваем значение счетчика семафора */
        ReleaseSemaphore(hResource, *lpdwCount + 1, NULL);

        /* увеличиваем значение счетчика 
           свободных ресурсов */
        dwResources += *lpdwCount;

        *lpdwCount = 0;

        LeaveCriticalSection(&section);
      }
      else                    /* закрепляем ресурс за собой */
      {
        *lpdwCount += 1;

        /* здесь будем изменять переменную, содержащую 
           количество свабодных ресурсов */
        EnterCriticalSection(&section);

        if (--dwResources == 0)
          SetEvent(hEmpty);             /* сигнализируем об 
                                        исчерпании ресурсов */

        LeaveCriticalSection(&section);
      }
    }
  }

  /* 
     завершаем поток и возвращаем 
     количество захваченных ресурсов 
  */
  return *lpdwCount;
}
