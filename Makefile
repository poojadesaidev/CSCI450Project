all:
	g++ serverM.cpp -o serverM -std=c++11
	g++ serverA.cpp -o serverA -std=c++11
	g++ serverB.cpp -o serverB -std=c++11
	g++ serverC.cpp -o serverC -std=c++11
	g++ client.cpp -o client -std=c++11
	g++ monitor.cpp -o monitor -std=c++11

clean:
	rm serverM serverA serverB serverC client monitor