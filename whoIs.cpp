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
map<string, int> macMapper;
map<string, int> ipMapper;

arpPacket atacante;
arpPacket victima;



string findMacOfSpoofer() {
    string macOfSpoofer = "no spoofing";
    map<string, int>::iterator it = macMapper.begin();
    for (it = macMapper.begin(); it != macMapper.end(); it++) {
        if (it->second > THRESHOLD) {
            //cout << "Mac of spoofer: " << it->first << endl;
              return it->first;
        }
    }
    return macOfSpoofer;
}


void findIPs(string sMacOfSpoofer, vector<arpPacket> packets) {
  map<string, int>::iterator it = ipMapper.begin();
  int iCont = 0;
  string matiPs[2][2];

  //meter al mapa
  for(int i = 0; i < packets.size(); i++){
      if(packets[i].sMac == sMacOfSpoofer){
          ipMapper[packets[i].sIp]++;
      }
  }

  for (it = ipMapper.begin(); it != ipMapper.end(); it++) {
      //cout << it->first << "->" << it->second << endl;
      matiPs[iCont][0] = it->first;
      matiPs[iCont][1] = it->second;
      iCont++;

  }

  if(matiPs[0][1] > matiPs[1][1] ){
      //cout << "IP of victim " << matiPs[0][0] << endl;
      victima.sIp = matiPs[0][0];
      //cout << "IP of attacker " << matiPs[1][0] << endl;
      atacante.sIp = matiPs[1][0];


  } else{
      //cout << "IP of victim " << matiPs[1][0] << endl;
      victima.sIp = matiPs[1][0];
      //cout << "IP of attacker " << matiPs[0][0] << endl;
      atacante.sIp = matiPs[0][0];
  }
}

void insertIntoMap(string mac) {
  macMapper[mac] = 0;
}

int optionDirfference(vector<arpPacket> packets) {
  int option = 0;

  for (int i = 0; i < packets.size(); i++) {
    if (packets[i].option == "2") {
      option++;
      macMapper[packets[i].sMac]++;
    }
    if (packets[i].option == "1") {
      option--;
      macMapper[packets[i].sMac]--;
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

void printAnswer(arpPacket victima, arpPacket atacante){

    cout << "  Mac of victim:  " << victima.sMac << endl;
    cout << "Mac of attacker:  " << atacante.sMac << endl;
    cout << "   IP of victim:  " << victima.sIp << endl;
    cout << " IP of attacker:  " << atacante.sIp << endl;
}

int main() {
  vector<arpPacket> packets;
  packets = writePacketstoFile();
  isSpoofing(packets);

  atacante.sMac = findMacOfSpoofer();
  findIPs(atacante.sMac, packets);

  printAnswer(victima, atacante);

}
