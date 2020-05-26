#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <QString>

class Exception {
public:
   Exception() {printError();}
   Exception(const QString& msg) : msg (msg) {printError();}
  ~Exception( ) {}
   QString getMessage( ) const {return(msg);}
   void printError() {std::cout << getMessage().toStdString() << std::endl;}

private:
   QString msg;
};


class FileNotOpenedException: public Exception {
private:
   std::string fileName;

public:
    FileNotOpenedException(QString fileName): Exception("File is not opened:" + fileName) {}
};

class WrongFileDataException: public Exception {
private:
   std::string fileName;

public:
    WrongFileDataException(QString fileName): Exception("File " + fileName + " has unparsable data") {}
};


#endif // EXCEPTIONS_H
