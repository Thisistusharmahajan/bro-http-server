#include<iostream>
#include <map>
#include <forward_list>
using namespace std;
// Amit the bro programmer
class Validator{
    private:
    Validator(){
        // constructor private so that this class can't be instantiated.
    }
    public:
    static bool isValidMIMEType(string &mimeType){
        // right now do nothing
        return true;
    }
    static bool isValidPath(string &path){
        // right now do nothing
        return true;
    }
    static bool isValidURLFormat(string &url){
        // right now do nothing
        return true;
    }
};
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
private:
string contentType;
forward_list<string> content;
forward_list<string>::iterator contentIterator;
// this is because we'll be accumulating whatever the content comes in the request and will dispatch everything by
// extracting it from this forward_list when time comes to dispatch it to client.
unsigned long contentLength;
public:
Response(){
this->contentLength = 0;
this->contentIterator = this->content.before_begin();
}
~Response(){
// not yet decided
}
void setContentType(string contentType){
    if(Validator::isValidMIMEType(contentType)){
        this->contentType = contentType;
    }
}

Response & operator <<(string content){
    this->contentLength+=content.length();
    this->contentIterator = this->content.insert_after(this->contentIterator,content);
    return *this;
}
};

class Bro{
public:
    Bro(){
    // constructor
    }
    ~Bro(){
    //destructor
    }
/*
the idea will be like we'll whenever request arrives our server will be looking up the map for url pattern the map 
will  be storing the urls in map urlMappings
the key wil be string url and value will be a pointer to a function whose parameters are Request & and Response & 
and return type as void
if not found the server will then consider it as static resource and it will be looked up in the static resources folder.
*/
private:
string staticResourcesFolder;
map<string, void (*)(Request &, Response &)> urlMappings;
public:
void setStaticResourcesFolder(string staticResourcesFolder){
    if(Validator::isValidPath(staticResourcesFolder)){
        this->staticResourcesFolder = staticResourcesFolder;
    }
}
void get(string url, void (*callBack)(Request &request, Response &response)){
    if(Validator::isValidURLFormat(url)){
        urlMappings.insert(pair<string, void (*)(Request &, Response &)>(url,callBack));
    }
}
void listen(int portNumber, void (*callBack)(Error &)){
    // do nothing right now
} 
};

// Bobby (web application programmer user of Bro server)

int main(){
    Bro bro;
    bro.setStaticResourcesFolder("whatever");
    bro.get("/", [](Request &request, Response &response){
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
    bro.get("/getCustomers",[](Request &request, Response &response){
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
    bro.listen(6060,[](Error &error){
        if(error.hasError())
        {
            cout<<error.getError();
            return;
        }
        cout<<"Bro Http Server is ready to Listen on Port 6060"<<endl;
    });
    return 0;

}