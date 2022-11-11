# makefile L4

.SUFFIXES: .class .java

PACK=L4
TARG=test
JC=javac -g
JM=java -ea -jar
JR=jar -cfe

OBJ=$(PACK)\boolVector.class \
    $(PACK)\test.class

.java.class:
	$(JC) $<

run: build
	$(JM) $(TARG).jar

build: 	$(OBJ)
	$(JR) $(TARG).jar $(PACK).test $(OBJ)

clean:
	for %%f in ($(OBJ)) do del %%f
	del $(TARG).jar

$(PACK)\boolVector.class: $(PACK)\boolVector.java makefile

$(PACK)\test.class: $(PACK)\test.java makefile

# eof makefile L4
