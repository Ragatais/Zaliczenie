#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>           //string compare

bool stringCompare(std::string left, std::string right)
{
    int size = 0;
    if (left.size() < right.size())
    {
        size = left.size();
    }
    else
    {
        size = right.size();                //ktory wyraz ma mniej liter
    }
    for (int i = 0; i < size; i++)
    {
        if (std::tolower(left[i]) > std::tolower(right[i]))         //wyrazy w zlej kolejnosci
        {
            return true;
        }
        else
        {
            if (std::tolower(left[i]) < std::tolower(right[i]))    //wyrazy w dobrej kolejnosci
            {
                return false;
            }
        }
    }
    return false;
}
void menu(bool sortType, bool sortOrder)
{
    std::cout << "\n1. Wczytaj.\nTyp sortowania: ";
    if (sortType)
    {
        std::cout << "Babelkowe\n";
    }
    else
    {
        std::cout << "Szybkie\n";
    }
    std::cout << "Kolejnosc sortowania: ";
    if (sortOrder)
    {
        std::cout << "A-Z\n";
    }
    else
    {
        std::cout << "Z-A\n";
    }
    std::cout << "2. Zmien tryb sortowania. \n3. Zmien kolejnosc sortowania. \n4. Sortuj. \n";
    std::cout << "5. Wyswietl najdluzszy i najkrotszy wyraz. \n6. Dodaj wyraz. \n";
    std::cout << "7. Usun wyraz. \n8. Wyswietl. \n9. Zapisz. \n10. Wyjdz. \n";
}
void readFromFile(std::vector<std::string>* dictionary)
{
    dictionary->clear();                                        //czysczenie tablicy na wypadek, gdyby byly w niej juz zapisane jakies dane
    std::fstream file;                                          //strumien danych z pliku
    std::string pathToFile, line;

    std::cout << "Podaj sciezke do pliku: ";
    std::cin >> pathToFile;

    file.open(pathToFile, std::ios::in);                         //otwieranie pliku w trtybie tylko do odczytu         
    int spacePosition;                                          //oddzielanie numeracji od wyrazow
    while (std::getline(file, line))
    {
        if (line != "l.p. word")
        {
            spacePosition = line.find(" ");
            if (spacePosition != -1)
                line = line.substr(spacePosition + 1);      //usuwanie numeracji
            dictionary->push_back(line);
        }
    }
    file.close();

    std::cout << "Plik zostal wczytany.\n";
}
void bubbleSort(std::vector<std::string>* dictionary)
{
    bool flag = true;
    std::string tmp;                                         //czy zostala dokonana jakas zmiana
    while (flag)
    {
        flag = false;
        for (int i = 0; i < dictionary->size() - 1; i++)
        {
            if (stringCompare((*dictionary)[i], (*dictionary)[i + 1]))      
            {
                flag = true;

                tmp = (*dictionary)[i];
                (*dictionary)[i] = (*dictionary)[i + 1];
                (*dictionary)[i + 1] = tmp;
            }
        }
    }
}
int part(std::vector<std::string>* dictionary, int start, int end)
{
    std::string x = (*dictionary)[(start + end) / 2];       //dictionary[srodek tablicy]
    int i = start, j = end;
    std::string tmp;
    while (1)
    {
        while (stringCompare((*dictionary)[j], x))          
        {
            j--;
        }
        while (stringCompare(x, (*dictionary)[i]))           
        {
            i++;
        }
        if (i < j)
        {
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
void length(std::vector<std::string> dictionary)
{
    std::string longest = "", shortest = dictionary[0];
    for (int i = 0; i < dictionary.size(); i++)
    {
        if ((dictionary)[i].length() > longest.length())
        {
            longest = (dictionary)[i];
        }
        if ((dictionary)[i].length() < shortest.length())
        {
            shortest = (dictionary)[i];
        }
    }
    std::cout << "Najdluzszy wyraz: " << longest << std::endl;
    std::cout << "Najkrotszy wyraz: " << shortest << std::endl;
}
void add(std::vector<std::string>* dictionary)
{
    std::string word;
    std::cout << "Podaj wyraz, ktory chcesz dodac: ";
    std::cin >> word;
    dictionary->push_back(word);

    std::cout << "Wyraz " << word << " zostal dodany do listy.\n";
}
void remove(std::vector<std::string>* dictionary)
{
    std::string word;
    bool flag = true;                           
    std::cout << "Podaj wyraz, ktory chcesz usunac: ";
    std::cin >> word;
    for (auto i = dictionary->begin(); i != dictionary->end(); )                              //iterator potrzebny do funkcji erase
    {
        if (*i == word)
        {
            dictionary->erase(i);
            flag = false;
            std::cout << "Wyraz " << word << " zostal usuniety z listy.\n";
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
    std::string header = "|l.p.", separator = "|", header1 = "word";
    int initialHeaderLength = header.length(), longest = 0;                         
    int max_length = std::to_string(dictionary.size()).length();                        
    for (int i = 0; i < dictionary.size(); i++)
    {
        if (dictionary[i].length() > longest)
        {
            longest = dictionary[i].length();
        }
    }
    if (max_length < initialHeaderLength)
    {
        max_length = initialHeaderLength;
    }
    else
    {
        for (int i = initialHeaderLength; i < max_length; i++)         
        {
            header += " ";
        }
    }
    header += "\t|" + header1;
    for (int i = header1.length(); i < longest; i++)
    {
        header += " ";
    }
    header += "|";
    for (int i = separator.length(); i < header.length(); i++)
    {
        separator += "-";
    }
    separator += "-|";
    std::cout << separator << std::endl;
    std::cout << header << std::endl;
    std::cout << separator << std::endl;
    for (int i = 0; i < dictionary.size(); i++)
    {
        std::cout << "|" << i + 1 << ".";
        for (int j = 0; j < max_length - std::to_string(i + 1).length(); j++)
        {
            std::cout << " ";
        }
        std::cout << "\t|" << dictionary[i];
        for (int j = dictionary[i].length(); j < longest; j++)
        {
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
        //std::cout << dictionary[i] << std::endl;
    }
    std::cout << separator;
}
void save(std::vector<std::string> dictionary)
{
    std::fstream file;
    std::string pathToFile;
    std::cout << "Podaj sciezke do zapisu: ";
    std::cin >> pathToFile;

    file.open(pathToFile, std::ios::out);                //jesli plik nie istnieje to zostaje utworzony
    file << "l.p. word\n";
    for (int i = 0; i < dictionary.size(); i++)
    {
        file << i + 1 << ". " << dictionary[i] << std::endl;
    }

    std::cout << "Plik zostal zapisany.\n";
}

int main()
{
    std::vector<std::string> dictionary;            //tablica bez deklarowanej wielkosci, typ string
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
            std::cout << "Typ sortowania zostal zmieniony.\n";
            break;
        case 3:
            sortOrder = !sortOrder;
            std::cout << "Kolejnosc sortowania zostala zmieniona.\n";
            break;
        case 4:
            if (sortType)
            {
                bubbleSort(&dictionary);
                std::cout << "Wyrazy zostaly posortowane.\n";
            }
            else
            {
                quickSort(&dictionary, 0, dictionary.size() - 1);
                std::cout << "Wyrazy zostaly posortowane.\n";
            }
            if (!sortOrder)
                reverse(&dictionary);
            break;
        case 5:
            length(dictionary);
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