#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct arpPacket{
  string option;
  string sMac;
  string sIp;
};

const int THRESHOLD = 5;
map<string, int> arpMapper;
void findSpoofer() {
  map<string, int>::iterator it = arpMapper.begin();

  for (it = arpMapper.begin(); it != arpMapper.end(); it++) {
    if (it->second > THRESHOLD) {
      cout << "Mac of spoofer: " << it->first << endl;
    }
  }
}

void insertIntoMap(string mac) {
  arpMapper[mac] = 0;
}

int optionDirfference(vector<arpPacket> packets) {
  int option = 0;

  for (int i = 0; i < packets.size(); i++) {
    if (packets[i].option == "2") {
      option++;
      arpMapper[packets[i].sMac]++;
    }
    if (packets[i].option == "1") {
      option--;
      arpMapper[packets[i].sMac]--;
    }
  }

  return option;
}

bool isSpoofing (vector<arpPacket> packets) {
  return optionDirfference(packets) >= THRESHOLD;
}

// Write packets to file
vector<arpPacket> writePacketstoFile() {
  vector<arpPacket> packets;
  ifstream myFile;

  myFile.open("arp.txt");
  string sOption;
  string sMac;
  string sIp;
  arpPacket aux;

  while (myFile >> sOption >> sMac >> sIp) {
    aux.option = sOption;
    aux.sMac = sMac;
    aux.sIp = sIp;
    insertIntoMap(sMac);
    packets.push_back(aux);
  }

  myFile.close();
  return packets;
}

int main() {
  vector<arpPacket> packets;
  packets = writePacketstoFile();
  isSpoofing(packets);
  findSpoofer();
}
