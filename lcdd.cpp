#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


#include <sys/time.h>
#include <sys/select.h>
#include <time.h>

#include "auxfunctions.h"

using std::cerr;
using std::endl;
using std::string;
using std::setw;
using std::setfill;
using std::min;
using std::max;

string line1;
string line2;
int index1;
int index2;
bool line1empty;
bool line2empty;

void daemonize() {
  int pid=fork();
  if (pid>0) {
    exit(0);
  } else if (pid<0) {
    cerr << "Could not fork to background" << endl;
    exit(-1);
  }
}

void write(bool increaseScroll=true) {
  string buffer;
	
	int length1=min(index1+16,(int) line1.length());
	int length2=min(index2+16,(int) line2.length());

	string l1=line1+"  **  ";
  string l2=line2+"  **  ";

	l1.resize(max((int) l1.length(), 16),' ');
	l2.resize(max((int) l2.length(), 16),' ');

	buffer = l1.substr(index1,l1.length())+line1;
	buffer.resize(16,' ');
  buffer += l2.substr(index2,l2.length())+line2;
  buffer.resize(32,' ');

	std::ofstream lcd("/dev/lcd0",std::ios::out);

	lcd << buffer;
	lcd.close();

	if (increaseScroll) {
		if (line1.length()>16) {
			index1++;
			if (index1>=line1.length()+6) {
				index1=0;
			}
		}
		if (line2.length()>16) {
			index2++;
			if (index2>=line2.length()+6) {
				index2=0;
			}
		}
	}
}

void printDate(bool dots=true) {
	//if there is text on both lines, do nothing
	if ( !(line1empty || line2empty) )
		return;
	
	timeval now;
	gettimeofday(&now,NULL);
	tm * datetime=localtime( &now.tv_sec );

	char timesep=(now.tv_usec>500000?':':' ');
  char datesep='/';
	
	std::stringstream datestr;
  std::stringstream timestr;
	
	datestr.str("");
	timestr.str("");

	// if both lines are empty, use long date format
	if (line1empty && line2empty) {
		switch (datetime->tm_wday) {
		case 1:
	    datestr << "Dill ";
			break;
		case 2:
			datestr << "Dima ";
			break;
		case 3:
			datestr << "Dime ";
			break;	
		case 4:
			datestr << "Dij  ";
			break;	
		case 5:
			datestr << "Div  ";
			break;	
		case 6:
			datestr << "Diss ";
			break;	
		case 7:
			datestr << "Dium ";
			break;
		}
		datestr << setw(2) << setfill('0') << datetime->tm_mday << " "; 
		switch (datetime->tm_mon) {
		case 1:
	    datestr << "Gen ";
			break;
		case 2:
			datestr << "Feb ";
			break;
		case 3:
			datestr << "Mar ";
			break;	
		case 4:
			datestr << "Abr ";
			break;	
		case 5:
			datestr << "Mai ";
			break;	
		case 6:
			datestr << "Jun ";
			break;	
		case 7:
			datestr << "Jul ";
			break;
		case 8:
	    datestr << "Ago ";
			break;
		case 9:
			datestr << "Set ";
			break;
		case 10:
			datestr << "Oct ";
			break;	
		case 11:
			datestr << "Nov ";
			break;	
		case 12:
			datestr << "Des ";
			break;	
		}
		datestr << datetime->tm_year+1900;
	  
	} else {
		datestr << 
			setw(2) << setfill('0') << datetime->tm_mday << datesep << 
			setw(2) << setfill('0') << datetime->tm_mon;
	}
	timestr <<
		setw(2) << setfill('0') << datetime->tm_hour << timesep <<
		setw(2) << setfill('0') << datetime->tm_min << timesep <<
		setw(2) << setfill('0') << datetime->tm_sec;

	if (line1empty && !line2empty) 
	  line1=datestr.str() + "   " + timestr.str();
	else if (!line1empty && line2empty) 
  	line2=datestr.str() + "   " + timestr.str();
  else {
  	line1=datestr.str();
		line2="    "+timestr.str()+"    ";
	}

}

int main(int argc, char *argv[]) {

  line1="";
  line2="";
  index1=0;
  index2=0;
  line1empty=(line1.empty());
  line2empty=(line2.empty());
 
  daemonize();
	
  if (argc>=2) {
    line1=argv[1];
		if (!line1.empty()) 
			line1.resize(max((int) line1.size(),16),' ');
  }
  if (argc >=3) {
    line2=argv[2];
  	if (!line2.empty()) 
			line2.resize(max((int) line2.size(),16),' ');
 }

	printDate();
	write();
  
  //open socket and listen...
  int sock=0;
  fd_set socket;
  int port=11111;
  struct sockaddr_in local;
  struct sockaddr remote;
  int error;

  FD_ZERO(&socket);

  sock=createSocket();

  local.sin_family=AF_INET;
  local.sin_addr.s_addr=INADDR_ANY;
  local.sin_port=htons(port);

  error=bindSocket(sock,&local);

  FD_SET(sock,&socket);
  if (error<0) {
    cerr << "Bind error" << endl;
    exit(error);
  }

  bool exit=false;

  char buffer[516];
  int longbuffer;
  string line;

  struct timeval timeout;

  socklen_t remoteSize=sizeof(remote);

  do {
    timeout.tv_sec=0;
    timeout.tv_usec=100000;

    error=select(sock+1,&socket,NULL,NULL,&timeout);
    if (!error) {
   
    } else {
      error=recvfrom(sock,buffer,512,0,&remote,&remoteSize);
    }

    line=buffer;

    line.resize(error);

    while ( (line[line.length()-1]=='\n') || 
	    (line[line.length()-1]=='\r'))
      line.resize(line.length()-1);

    if (line.size()!=0) {

      if (line=="quit") {
				exit=true;
      } else if (line[0]=='1') { //top line
				line1=line.substr(1,line.length()-1);
		  	if (!line1.empty()) 
					line1.resize(max((int) line1.size(),16),' ');
 				index1=0;
				line1empty=line1.empty();
      } else if (line[0]=='2') { //bottom line
				line2=line.substr(1,line.length()-1);
		  	if (!line2.empty()) 
					line2.resize(max((int) line2.size(),16),' ');
 				index2=0;
				line2empty=line2.empty();
      }
      
    }

    FD_ZERO(&socket);
    FD_SET(sock,&socket);
    write();
    printDate();
   
  } while(!exit);

  if (sock) close(sock);

  return 0;
}
