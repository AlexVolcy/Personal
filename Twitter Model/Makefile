CXX = g++
CPPFLAGS = -g -std=c++11 -Wall


all: twitter

twitter: twitter.cpp user.o datetime.o twiteng.o tweet.o handler.o cmdHandler.o util.o hash.o
	$(CXX) $(CPPFLAGS) $^ -o $@

datetime.o: datetime.cpp datetime.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

user.o: user.cpp user.h msort.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

tweet.o: tweet.cpp tweet.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

hash.o: hash.cpp hash.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

twiteng.o: twiteng.cpp twiteng.h tagdata.h heap.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

handler.o: handler.cpp handler.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

cmdHandler.o: cmdhandler.cpp cmdhandler.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

util.o: util.cpp util.h
	$(CXX) $(CPPFLAGS) -c $< -o $@


clean:
	rm *.o 
	rm twitter
	rm *.feed
	rm *.mentions
