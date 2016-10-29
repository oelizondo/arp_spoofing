#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct arpPacket{
  string option;
  string sMac;
  string sIp;

<<<<<<< HEAD
  arpPacket(string op, string mac, string ip) : option(op), sMac(mac), sIp(ip){}
=======
  // arpPacket(string op, string mac, string ip) : option(op), sMac(mac), sIp(ip){}

>>>>>>> 24b18c76742ab65301f1a9df1e8e8aebba491819
};


void readFile(ifstream myFile, string fileName, vector<arpPacket> v){

  myFile.open(fileName);
  string sOption;
  string sMac;
  string sIp;

  while (myFile >> sOption >> sMac >> sIp) {
    arpPacket aux;
    aux.option = sOption;
    aux.sMac = sMac;
    aux.sIp = sIp;
    v.push_back(aux);

  }

  myFile.close();
}

int main() {


  ifstream myFile;
  string fileName = "arp.txt";
  vector<arpPacket> packets;

  readFile(myFile, fileName, packets);

  //cout << packets[1].option << endl;
  //cout << packets[2].option << endl;
}
