// import std;
#include <string>
#include <iostream>
#include <algorithm>
#include <httplib.h>
using namespace std;
bool Debug = false;
int ServerPort = 9487;
int main() {
	Debug = true;
	if (Debug == true) {
		ServerPort = 8080;}
	else if(Debug == false){
		ServerPort = 9487;}
	httplib::Server server;
	server.Get("/get_my_ip", [](const httplib::Request& ClientRequest, httplib::Response& res) {
		auto& ClientHost = (*ClientRequest.headers.find("Host")).second;
		res.set_content(ClientHost, "text/plain");
		});
	server.listen("0.0.0.0", ServerPort);

}