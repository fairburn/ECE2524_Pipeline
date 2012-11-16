all: consumer generator dispatcher

consumer:
	g++ -o consumer consumer.cpp

generator:
	g++ -o generator generator.cpp
	
dispatcher:
	g++ -o dispatcher dispatcher.cpp

clean:
	rm generator consumer dispatcher