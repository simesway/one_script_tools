#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
using std::cout, std::endl, std::setw, std::setfill, std::string;

string tagdbinfo = "/home/eiber/my-own-programs/tagdb/tagdb-info";
string tagdbentries = "/home/eiber/my-own-programs/tagdb/tagdb-entries";

void printHead(){
    std::ifstream file(tagdbinfo);
    string line;
    for(int i = 0; i < 11; i++) {
        std::getline(file, line);
        cout << line << endl;
    } 
    file.close();
}

std::vector<string> vectorize(string location){
    std::ifstream file(location);
    std::vector<string> entries;
    string entry;
    while(getline(file, entry)) entries.push_back(entry);
    file.close();
    return entries;
}

void save_to_file(std::vector<string> lines, string location){
    std::ofstream out(location);
    for(int i = 0; i < lines.size(); i++) out << lines[i] << endl;
    out.close(); 
}

void appenddb(int argc, char **argv){ // Eintrag hinzufügen
    if(string(argv[1]) == "-a" && argc >= 4){
        
        std::vector<string> entries = vectorize(tagdbentries); 
        
        std::ostringstream oss; // programmargumente in oss leiten
        for(int j = 2; j <= argc; j++) oss << argv[j]<< " ";
        oss << endl;

        entries.push_back(oss.str()); // oss in vector einfügen

        save_to_file(entries, tagdbentries);

        cout << "Entry added!" << endl;
    }else std::cerr << "Tag and entry required" << endl;
}

void findtags(int argc, char **argv){
    if(string(argv[1]) == "-t"){
        printHead(); 
        
        cout << " Entries tagged with:";
        for(int i = 2; i <= argc-1; i++) cout << " " << argv[i];
        cout << endl << endl;
         
        cout << setw(3) << "ID" << setw(25) << "TAGS" << "    |    " << "ENTRY" << endl;
        
        std::ifstream file(tagdbentries);
        string tags, data;

        int j = 1, numberfound = 0;
        
        std::ostringstream oss;
        string temp, line;
        while(getline(file, line)){
            std::istringstream iss(line);	
            iss >> tags;
            while(iss >> temp) oss << temp << " ";
                            
            int equaltags = 0;
            for(int i = 2; i <= argc-1; i++){
                if(tags.find(argv[i]) != std::string::npos) ++equaltags; }

            if(equaltags == (argc - 2))
            {
                cout << setfill(' ') << setw(3) << j << " " << setw(27) << setfill('.') << tags << " | " << oss.str() << endl;
                numberfound++;        
            }
            oss.str("");
            j++;
        }
        file.close();

        cout << endl << " " << numberfound << " tagged entrie(s) found // " << j-1 << " entrie(s) in total!" << endl << endl;        
    }
}

void list_and_delete(int argc, char **argv){
    if((string(argv[1]) == "-ll") || (string(argv[1]) == "-rm") || (string(argv[1]) == "-ls")){
        printHead();
        
        cout << " Entries:" << endl << endl;
        
        if((string(argv[1]) == "-ll") || (string(argv[1]) == "-rm"))
           cout << setw(3) << "ID" << setw(25) << "TAGS" << "    |    " << "ENTRY" << endl;
        if(string(argv[1]) == "-ls")
           cout << setw(3) << "ID" << setw(17)  << "ENTRY" << endl;
        
        std::ifstream file(tagdbentries);
        string tags, data;
        
        int count = 1;

        std::ostringstream oss;
        string temp, line;
        while(getline(file, line)){
            std::istringstream iss(line);	
            iss >> tags;
            while(iss >> temp) oss << temp << " ";
                            
            if((string(argv[1]) == "-ll") || (string(argv[1]) == "-rm")) 
                cout << setfill(' ') << setw(3) << count << " " << setw(27) << setfill('.') << tags << " | " << oss.str() << endl;

            if(string(argv[1]) == "-ls") 
                cout << setfill(' ') << setw(3) << count << " " << setw(8) << setfill('.') << " " << oss.str() << endl;
            
            oss.str(""); 

            count++;
        }	
        file.close();

        cout << endl;

        if(string(argv[1]) == "-rm"){
            cout << " ID of the item to be removed: (ID = 0 to quit)" << endl << " >>> ";
            
            int removeindex;
            int k = 1; 
            while(std::cin >> removeindex){
                if(removeindex == 0){
                    cout << " --> Deleting quitted" << endl;
                    cout << " --> " << k-1 << " entrie(s) removed | " << count-k << " remaining" << endl << endl;
                    return;
                } 

                std::vector<string> dblines = vectorize(tagdbentries);

                for(int i = removeindex - k; i < dblines.size() - 1; ++i) dblines[i] = dblines[i+1];
                
                dblines.pop_back();

                save_to_file(dblines, tagdbentries);

                cout << " --> Entry deleted" << endl;
                if((count - k - 1 ) == 0){
                    cout << " --> Deleting quitted" << endl << " --> No entries remaining" << endl;
                    cout << " --> " << k << " entrie(s) removed" << endl << endl;
                    return;
                } 
                k++;
                cout << " >>> ";
            }
        }        
    }
}

void printFile(int argc, char **argv){
    if((string(argv[1]) == "-h") || (string(argv[1]) == "--help")){
        std::ifstream infofile(tagdbinfo); 
        string line;
        while(getline(infofile, line)) 
            cout << line << endl;
    }
}

int main(int argc, char **argv){

    appenddb(argc, argv);    
    findtags(argc, argv);
    list_and_delete(argc, argv);
    printFile(argc, argv);

    return 0;
}
