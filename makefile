processor: errors.o MacroTable.o file_methods.o registers.o processor_commands.o SymbolsTable.o assemblerArrays.o commands_words.o externEntryTables.o secondPass.o firstPass.o base32.o pre_processor.o post_processor.o proccessor.o
	gcc -ansi -Wall -pedantic -g errors.o MacroTable.o file_methods.o registers.o processor_commands.o SymbolsTable.o assemblerArrays.o commands_words.o externEntryTables.o secondPass.o firstPass.o base32.o pre_processor.o post_processor.o proccessor.o -o processor

proccessor.o: proccessor.c pre_processor.h firstPass.h post_processor.h
	gcc -c -ansi -Wall -pedantic proccessor.c -o proccessor.o

post_processor.o: post_processor.c post_processor.h base32.h commands_words.h
	gcc -c -ansi -Wall -pedantic post_processor.c -o post_processor.o

pre_processor.o: pre_processor.c pre_processor.h file_methods.h MacroTable.h processor_commands.h
	gcc -c -ansi -Wall -pedantic pre_processor.c -o pre_processor.o

firstPass.o: firstPass.c firstPass.h secondPass.h
	gcc -c -ansi -Wall -pedantic firstPass.c -o firstPass.o

secondPass.o: secondPass.c secondPass.h commands_words.h
	gcc -c -ansi -Wall -pedantic secondPass.c -o secondPass.o

commands_words.o: commands_words.c commands_words.h assemblerArrays.h
	gcc -c -ansi -Wall -pedantic commands_words.c -o commands_words.o

assemblerArrays.o: assemblerArrays.c assemblerArrays.h externEntryTables.h
	gcc -c -ansi -Wall -pedantic assemblerArrays.c -o assemblerArrays.o

externEntryTables.o: externEntryTables.c externEntryTables.h SymbolsTable.h base32.h
	gcc -c -ansi -Wall -pedantic externEntryTables.c -o externEntryTables.o

SymbolsTable.o: SymbolsTable.c SymbolsTable.h processor_commands.h
	gcc -c -ansi -Wall -pedantic SymbolsTable.c -o SymbolsTable.o

processor_commands.o: processor_commands.c processor_commands.h errors.h registers.h
	gcc -c -ansi -Wall -pedantic processor_commands.c -o processor_commands.o

registers.o: registers.c registers.h 
	gcc -c -ansi -Wall -pedantic registers.c -o registers.o

file_methods.o: file_methods.c file_methods.h
	gcc -c -ansi -Wall -pedantic file_methods.c -o file_methods.o

base32.o: base32.c base32.h
	gcc -c -ansi -Wall -pedantic base32.c -o base32.o

MacroTable.o: MacroTable.c MacroTable.h
	gcc -c -ansi -Wall -pedantic MacroTable.c -o MacroTable.o

errors.o: errors.c errors.h
	gcc -c -ansi -Wall -pedantic errors.c -o errors.o


