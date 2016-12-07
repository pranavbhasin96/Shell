shell: \
		CDcommand.o \
		commandExecute.o \
		commandLaunch.o \
		ECHOcommand.o \
		EXITcommand.o \
		fg.o \
		getCurrentDir.o \
		killallbg.o \
		listjobs.o \
		main.o \
		pinfo.o \
		PWDcommand.o \
		sendsig.o \
		setInput.o \
		setOutput.o \
		split.o \
		terminal_init.o 
	$(CC) -g -o shell $^

clean:
	@rm -f *.o shell

main.o: mylib.h main.c
	$(CC) -g -c main.c

CDcommand.o: mylib.h src/CDcommand.c
	$(CC) -g -c src/CDcommand.c

commandExecute.o: mylib.h src/commandExecute.c
	$(CC) -g -c src/commandExecute.c

commandLaunch.o: mylib.h src/commandLaunch.c
	$(CC) -g -c src/commandLaunch.c

EXITcommand.o: mylib.h src/EXITcommand.c
	$(CC) -g -c src/EXITcommand.c

ECHOcommand.o: mylib.h src/ECHOcommand.c
	$(CC) -g -c src/ECHOcommand.c

fg.o: mylib.h src/fg.c
	$(CC) -g -c src/fg.c

getCurrentDir.o: mylib.h src/getCurrentDir.c
	$(CC) -g -c src/getCurrentDir.c

killallbg.o: mylib.h src/killallbg.c
	$(CC) -g -c src/killallbg.c

listjobs.o: mylib.h src/listjobs.c
	$(CC) -g -c src/listjobs.c

pinfo.o: mylib.h src/pinfo.c
	$(CC) -g -c src/pinfo.c

PWDcommand.o: mylib.h src/PWDcommand.c
	$(CC) -g -c src/PWDcommand.c

sendsig.o: mylib.h src/sendsig.c
	$(CC) -g -c src/sendsig.c

setInput.o: mylib.h src/setInput.c
	$(CC) -g -c src/setInput.c

setOutput.o: mylib.h src/setOutput.c
	$(CC) -g -c src/setOutput.c

split.o: mylib.h src/split.c
	$(CC) -g -c src/split.c

terminal_init.o: mylib.h src/terminal_init.c
	$(CC) -g -c src/terminal_init.c
