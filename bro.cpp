#include<iostream>
using namespace std;
// Amit the bro programmer
class Error{
    public:
    bool hasError(){
        return false;
    }
    string getError(){
        return "";
    }
};

class Request{

};

class Response{
public:
void setContentType(string contentType){
    // do nothing right now
}

Response & operator <<(string content){
    // right now do nothing
    return *this;
}
};

class Bro{
public:
void setStaticResourcesFolder(string staticResourcesFolder){
    // do nothing
}
void get(string urlPattern, void (*callBack)(Request &request, Response &response)){
    // do nothing right now
}
void listen(int portNumber, void (*callBack)(Error &)){
    // do nothing right now
}
};




// Bobby (web application programmer user of Bro server)

int main(){
    Bro bro;
    bro.setStaticResourcesFolder("whatever");
    bro.get("/",[](Request &request, Response &response) void {
        const char *html = R"""(
        <!DOCTYPE HTML>
        <html lang='en'>
        <head>
        <meta charset='utf-8'>
        <title>Whatever</title>
        </head>
        <body>
        <h1>Welcome</h1>
        <h3>Some Text</h3>
        <a href='getCustomers'>Customers List</a>
        </body>
        </html> 
        )""";
        response.setContentType("text/html"); // Setting MIME Type
        response<<html;
        // so whenever a request arrives / with no resource name this function will get executed and this html will get dispatch
    });
    bro.get("/getCustomers",[](Request &request, Response &response) void{
        const char *html = R"""(
            <!DOCTYPE HTML>
            <html lang='en'>
            <head>
            <meta charset='utf-8'>
            <title> Whatever </title>
            </head>
            <body>
            <h1>List of Customers</h1>
            <ul>
            <li>Ramesh</li>
            <li>Suresh</li>
            <li>Mohan</li>
            </ul>
            <a href='/'>Home</a>
            </body>
            </html>
        )""";
        response.setContentType("text/html"); // setting MIME Type
        response<<html;
    }
);
    bro.listen(6060,[](Error &error) void{
        if(error.hasError())
        {
            cout<<error.getError();
            return;
        }
        cout<<"Bro Http Server is ready to Listen on Port 6060"<<endl;
    });
    return 0;

}