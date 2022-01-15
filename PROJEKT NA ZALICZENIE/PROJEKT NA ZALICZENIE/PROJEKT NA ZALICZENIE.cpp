#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void menu(bool sortType, bool sortOrder)
{
    std::cout << "\n1. Wczytaj. \nTyp sortowania: ";
    if (sortType)
    {
        std::cout << "Babelkowe \n";
    }
    else
    {
        std::cout << "Szybkie \n";
    }
    std::cout << "Kolejnosc sortowania: ";
    if (sortOrder)
    {
        std::cout << "A-Z \n";
    }
    else
    {
        std::cout << "Z-A \n";
    }
    std::cout << "2. Zmien tryb sortowania. \n3. Zmien kolejnosc sortowania. \n4. Sortuj. \n";
    std::cout << "5. Wyswietl najdluzszy i najkrotszy wyraz. \n6. Dodaj wyraz. \n";
    std::cout << "7. Usun wyraz. \n8. Wyswietl. \n9. Zapisz. \n10. Wyjdz. \n";
}
void readFromFile(std::vector<std::string>* dictionary)
{
    dictionary->clear();
    std::fstream file;
    std::string pathToFile, line;

    std::cout << "Podaj sciezke do pliku: ";
    std::cin >> pathToFile;

    file.open(pathToFile,std::ios::in);
    int spacePosition;
    std::getline(file, line);
    do
    {
        std::getline(file, line);
        spacePosition = line.find(" ");
        if(spacePosition!=-1)
            line = line.substr(spacePosition+1);
        dictionary->push_back(line);
    } while (line != "");

    dictionary->pop_back();
    file.close();
}
void bubbleSort(std::vector<std::string>* dictionary)
{
    bool flag = true;
    while (flag)
    {
        flag = false;
        for(int i=0; i<dictionary->size()-1; i++ )
        {
            if ((*dictionary)[i] > (*dictionary)[i + 1])
            {
                flag = true;
                std::string tmp;
                
                tmp = (*dictionary)[i];
                (*dictionary)[i] = (*dictionary)[i + 1];
                (*dictionary)[i + 1] = tmp;
            }
        }
    }
}
int part(std::vector<std::string>* dictionary, int start, int end)
{
    std::string x = (*dictionary)[(start + end) / 2];
    int i = start, j = end;
    while (1)
    {
        while ((*dictionary)[j] > x)
        {
            j--;
        }
        while ((*dictionary)[i] < x)
        {
            i++;
        }
        if (i < j)
        {
            std::string tmp;

            tmp = (*dictionary)[i];
            (*dictionary)[i] = (*dictionary)[j];
            (*dictionary)[j] = tmp;
            i++;
            j--;
        }
        else
        {
            return j;
        }

    }
}
void quickSort(std::vector<std::string>* dictionary, int start, int end)
{
    int middle = 0;
    if (start < end)
    {
        middle = part(dictionary, start, end);
        quickSort(dictionary, start, middle);
        quickSort(dictionary, middle + 1, end);

    }
}
void reverse(std::vector<std::string>* dictionary)
{
    int j = dictionary->size()-1;
    for (int i = 0; i < dictionary->size()/2; i++)
    {

        std:: string tmp = (*dictionary)[i];
        (*dictionary)[i] = (*dictionary)[j];
        (*dictionary)[j] = tmp;
        j--;

    }
}
void length(std::vector<std::string>* dictionary)
{
    int longest=0, shortest=INT_MAX, longestPosition=0, shortestPosition=8;
    for (int i = 0; i < dictionary->size(); i++)
    {
        if ((*dictionary)[i].length() > longest)
        {
            longest = (*dictionary)[i].length();
            longestPosition = i;
        }
        if ((*dictionary)[i].length() < shortest)
        {
            shortest = (*dictionary)[i].length();
            shortestPosition = i;
        }
    }
    std::cout << "Najdluzszy wyraz: " << (*dictionary)[longestPosition] << std::endl;
    std::cout << "Najkrotszy wyraz: " << (*dictionary)[shortestPosition] << std::endl;
}
void add(std::vector<std::string>* dictionary)
{
    std::string word;
    std::cout << "Podaj wyraz, ktory chcesz dodac: ";
    std::cin >> word;
    dictionary->push_back(word);
}
void remove(std::vector<std::string>* dictionary)
{
    std::string word;
    bool flag = true;
    std::cout << "Podaj wyraz, ktory chcesz usunac: ";
    std::cin >> word;
    for (auto i = dictionary->begin(); i != dictionary->end(); )
    {
        if (*i == word)
        {
            dictionary->erase(i);
            flag = false;
            break;
        }
        else
        {
            ++i;
        }
    }
    if (flag)
    {
        std::cout << "Podany wyraz: " << word <<" nie istnieje w zbiorze.\n";
    }
}
void display(std::vector<std::string> dictionary)
{
    for (auto i = dictionary.begin(); i != dictionary.end(); i++)
    {
        std::cout << *i << std::endl;
    }
}
void save(std::vector<std::string> dictionary)
{
    std::fstream file;
    std::string pathToFile;
    int iterator = 1;
    std::cout << "Podaj sciezke do pliku: ";
    std::cin >> pathToFile;

    file.open(pathToFile,std::ios::out);
    file << "l.p.  word \n";
    for (auto i = dictionary.begin(); i < dictionary.end(); i++)
    {
        
        file<< iterator << " " << *i << std::endl;
        iterator++;
    }
}

int main()
{
    std::vector<std::string> dictionary;
    bool sortType = true, sortOrder = true;
    int choice = 0;
    
    while (choice != 10)
    {
        menu(sortType, sortOrder);
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            readFromFile(&dictionary);
            break;
        case 2:
            sortType = !sortType;
            break;
        case 3:
            sortOrder = !sortOrder;
            break;
        case 4:
            if (sortType)
                bubbleSort(&dictionary);
            else
                quickSort(&dictionary, 0, dictionary.size()-1);
            if (!sortOrder)
                reverse(&dictionary);
            break;
        case 5:
            length(&dictionary);
            break;
        case 6:
            add(&dictionary);
            break;
        case 7:
            remove(&dictionary);
            break;
        case 8:
            display(dictionary);
            break;
        case 9:
            save(dictionary);
            break;
        case 10:
            return 0;
            break;
        default:
            std::cout << "Podano wartosc spoza zakresu.\n";
            break;
        }
    }
}