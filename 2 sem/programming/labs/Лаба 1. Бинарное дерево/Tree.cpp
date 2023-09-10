#include "Tree.h"
Tree::TreeItem* Tree::Clone(TreeItem* Tr)
{
	if (Tr == NULL)
		return NULL;
	TreeItem* New = new TreeItem;
	New->Info = Tr->Info;
	New->LSon = Clone(Tr->LSon);
	New->RSon = Clone(Tr->RSon);
	return New;
}

void Tree::Erase()
{
	DeleteTree(Root);
	Root = NULL;
}

Tree::~Tree()
{
	Erase();
}

void Tree::DeleteTree(TreeItem* t)
{
	if (t != NULL)
	{
		DeleteTree(t->LSon);
		DeleteTree(t->RSon);
		delete t;
	}
}

Tree::Tree(const Tree& L)
{
	Root = Clone(L.Root);
}

const Tree& Tree::operator = (const Tree& L)
{
	if (&L == this)
		return *this;
	Erase();
	Root = Clone(L.Root);
	return *this;
}

bool Tree::Find(int e, TreeItem*& t)
{
	if (Root == NULL)
	{
		t = NULL;
		return false;
	}
	t = Root;
	while (true)
	{
		if (t->Info == e)
		{
			return true;
		}
		if (t->Info > e)
		{
			if (t->LSon == NULL)
				return false;
			t = t->LSon;
		}
		else
		{
			if (t->RSon == NULL)
				return false;
			t = t->RSon;
		}
	}
}

bool Tree::Add(int e)
{
	int ch = 0;
	TreeItem* s = new TreeItem;
	if (Find(e, s))
		return false;
	if (Root == NULL)
	{
		TreeItem* p = new TreeItem;
		Root = p;
		p->Info = e;
		p->Father = NULL;
		return true;
	}
	else
	{
		TreeItem* p = new TreeItem;
		p = Root;
		TreeItem* q = new TreeItem;
		q->Info = e;
		while (true)
		{
			if (p->Info > e)
			{
				if (p->LSon == NULL)
				{
					p->LSon = q;
					q->Father = p;
					return true;
				}
				else
				{
					p = p->LSon;
				}
			}
			else
			{
				if (p->RSon == NULL)
				{
					q->Father = p;
					p->RSon = q;
					return true;
				}
				else
				{
					p = p->RSon;
				}
			}
		}
	}
}

bool Tree::FindByValue(int a, int& t)
{
	if (Root == NULL)
	{
		return false;
	}
	TreeItem* temp = new TreeItem;
	temp = Root;
	for (;;)
	{
		if (temp->Info == a)
		{
			t++;
			return true;
		}
		if (temp->Info > a)
		{
			t++;
			if (temp->LSon == NULL)
				return false;
			temp = temp->LSon;
		}
		else
		{
			t++;
			if (temp->RSon == NULL)
				return false;
			temp = temp->RSon;
		}
	}

}

bool Tree::Remove(int e)
{
	TreeItem* s;
	TreeItem* q;
	if (!Find(e, s))
		return false;
	else
	{
		if ((s->LSon != NULL) && (s->RSon != NULL))
		{
			q = s->RSon;
			while (q->LSon != NULL)
				q = q->LSon;
			s->Info = q->Info;
			EraseTree(q);
		}
		else
			EraseTree(s);
		return true;
	}
}

void Tree::EraseTree(TreeItem*& s)
{
	TreeItem* q;
	if (s->LSon != NULL)
		q = s->LSon;
	else
		q = s->RSon;
	if (q != NULL)
		q->Father = s->Father;
	if (s->Father == NULL)
		Root = q;
	else
		if ((s->Father)->LSon == s)
			(s->Father)->LSon = q;
		else
			(s->Father)->RSon = q;
	delete s;
	s = NULL;
}

void Tree::Walk(TreeItem* Root, void Pri(int&)) const
{
	if (Root == NULL)
	{
		return;
	}
	Walk(Root->LSon, Pri);
	Pri(Root->Info);
	Walk(Root->RSon, Pri);
}

void Tree::Walk(void Pri(int&)) const
{

	if (Root != NULL)
	{
		Walk(Root->LSon, Pri);
		Pri(Root->Info);
		Walk(Root->RSon, Pri);
	}
}