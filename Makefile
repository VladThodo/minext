 # Simple make file used for building minext from source
 # It's worth noting that I'm not the best when it comes to writing make files
 
minext: # Building the main executable file
	@gcc -o bin/minext src/texedit.c

run: minext	# Running  the executable produced by minext
	@chmod +x bin/minext
	@./bin/minext