#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;
namespace fs = filesystem;

int main(int argc, char *argv[])
{
    if(argc < 3) {
        cout << "Err: Please enter ./main (project_dir) (template_dir)" << endl;
        return 0;
    }

    string path = argv[1];
    string templateDir = argv[2];

    string clientSelected; 
    string postName;

    vector<string> clients;
    time_t t = time(0);
    tm* now = localtime(&t);

    for (const auto & entry : fs::directory_iterator(path)) {
        clients.push_back(entry.path().filename().string());
    }

    for (size_t i = 0; i < clients.size(); ++i)
    {
        cout << (i + 1) << " - " << clients[i] << endl;
    }
    cout << "" << endl;
    cout << "Selecione o Cliente: ";
    getline(cin, clientSelected);

    if(stoi(clientSelected) > clients.size()) {
        return 0;
    }
    cout << "" << endl;
    cout << "Cliente Selecionado: " << clients[stoi(clientSelected) - 1] << endl;
    cout << "" << endl;
    cout << "Coloque o nome do Post: ";
    getline(cin, postName);
    
    ostringstream ss;
    ss << put_time(now, "%y %m %d");

    fs::copy(
        templateDir, 
        path + "/" + clients[stoi(clientSelected) - 1] + "/" + ss.str() + " - " + postName,
        fs::copy_options::recursive
    );

    return 0;
}