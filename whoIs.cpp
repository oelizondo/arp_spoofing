#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct arpPacket{
  string option;
  string sMac;
  string sIp;
};


void writePacketstoFile() {
  vector<arpPacket> packets;
  ifstream myFile;
  string fileName = "arp.txt";

  myFile.open(fileName);
  string sOption;
  string sMac;
  string sIp;
  arpPacket aux;

  while (myFile >> sOption >> sMac >> sIp) {
    aux.option = sOption;
    aux.sMac = sMac;
    aux.sIp = sIp;
    packets.push_back(aux);
  }

  myFile.close();
}

int main() {
  writePacketstoFile();
}
