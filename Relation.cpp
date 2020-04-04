#include<iostream>
#include<cstdlib>
#include<cstdarg>

using namespace std;

class MyRelation 
{
    private:
        int firstSize;
        int secondSize;
        int *firstSet;
        int *secondSet;
        int **relation;
    public:
        // Default Constructor to initialise the instance variables
        MyRelation() 
        {
            firstSize = 0;
            secondSize = 0;
            firstSet = NULL;
            secondSet = NULL;
            relation = NULL;
        }

        // Function to print Relation Matrix
        void printRelation()
        {
            for(int row = 0; row < firstSize; ++row)
            {
                for(int column = 0; column < secondSize; ++column)
                    cout << relation[row][column] << " ";
                cout << endl;
            }
        }

        // Function to print closure
        void printClosure(int **temp)
        {
            for(int row = 0; row < firstSize; ++row)
            {
                for(int column = 0; column < secondSize; ++column)
                    cout << temp[row][column] << " ";
                cout << endl;
            }
        }

        // Function to enter the size and elements in sets and relation
        void enterValues(bool setChoice)
        {
            cout << "\tFIRST SET\n";
            cout << "Enter the size of first Set: ";
            cin >> firstSize;

            firstSet = new int[firstSize];

            cout << "Enter the elements in first Set...\n";
            for(int index = 0; index < firstSize; ++index)
                cin >> firstSet[index];

            system("cls");

            if(setChoice == true)
            {
                cout << "\tSECOND SET\n";
                cout << "Enter the size of second Set: ";
                cin >> secondSize;

                secondSet = new int[secondSize];

                cout << "Enter the elements in second Set...\n";
                for(int index = 0; index < secondSize; ++index)
                    cin >> secondSet[index];

                system("cls");
            }
            else
            {
                secondSize = firstSize;
                secondSet = firstSet;
            }

            relation = new int*[firstSize];
            for(int index = 0; index < firstSize; ++index)
                relation[index] = new int[secondSize];

            cout << "\tRELATION\n";
            cout << "Enter the relation in the matrix form (row wise) (1 or 0)...\n";
            for(int row = 0; row < firstSize; ++row)
                for(int column = 0; column < secondSize; ++column)
                    cin >> relation[row][column];

            system("cls");
        }

        // Function to check the reflexivity of the relation
        bool isReflexive()
        {
            int answer = 1;
            for(int row = 0; row < firstSize; ++row)
                for(int column = 0; column < secondSize; ++column)
                    if(row == column)
                        if(relation[row][column] != 1)
                            answer = 0;
            if(answer == 0)
                return false;
            else
                return true;
        }

        // Function to check the symmetricity of the relation
        bool isSymmetric()
        {
            int answer = 1;
            for(int row = 0; row < firstSize; ++row)
                for(int column = 0; column < secondSize; ++column)
                    if(relation[row][column] == 1 && relation[column][row] != 1)
                        answer = 0;
            if(answer == 0)
                return false;
            else
                return true;
        }

        // Function to check the anti-symmetricity of the relation
        bool isAntiSymmetric()
        {
            int answer = 1;
            for(int row = 0; row < firstSize; ++row)
                for(int column = 0; column < secondSize; ++column)
                    if(relation[row][column] == 1 && relation[column][row] == 1 && row != column)
                        answer = 0;
            if(answer == 0)
                return false;
            else
                return true;
        }

        // Function to check the transitivity of the relation
        bool isTransitive()
        {
            int answer = 1;
            for(int row = 0; row < firstSize; ++row)
                for(int column = 0; column < secondSize; ++column)
                    for(int element = 0; element < secondSize; ++element)
                        if(relation[row][column] == 1 && relation[column][element] == 1 && relation[row][element] != 1)
                            answer = 0;
            if(answer == 0)
                return false;
            else
                return true;
        }

        // Function to check whether relation is equivalence relation or not
        bool isEquivalence(bool reflexive, bool symmetric, bool transitive)
        {
            if(reflexive == true && symmetric == true && transitive == true)
                return true;
            else
                return false;
        }

        // Function to check whether relation is partial order relation or not
        bool isPartial(bool reflexive, bool antisymmetric, bool transitive)
        {
            if(reflexive == true && antisymmetric == true && transitive == true)
                return true;
            else
                return false;
        }

        // Function to find reflexive closure of the relation
        int** refClosure()
        {
            int **temp = relation;
            for(int row = 0; row < firstSize; ++row)
                for(int column = 0; column < secondSize; ++column)
                    if(row == column)
                        temp[row][column] = 1;
            return temp;
        }

        // Function to find symmetric closure of the relation
        int** symClosure()
        {
            int **temp = relation;
            for(int row = 0; row < firstSize; ++row)
                for(int column = 0; column < secondSize; ++column)
                    if(temp[row][column] == 1 && temp[column][row] != 1)
                        temp[column][row] = 1;
            return temp;
        }

        // Function to find transitive closure of the relation
        int** transClosure()
        {
            int **temp = relation;
            int max = (firstSize > secondSize) ? firstSize : secondSize;
            for(int element = 0; element < max; ++ element)
                for(int row = 0; row < firstSize; ++row)
                    for(int column = 0; column < secondSize; ++column)
                        temp[row][column] = temp[row][column] || (temp[row][element] && temp[element][column]);
            return temp;
        }

};

int main()
{
    bool setChoice, reflexive, symmetric, antisymmetric, transitive;
    int **temp;
    char choice;

    do
    {
        cout << "Is the binary relation is on two distinct sets? (1 for yes OR 0 for no) : ";
        cin >> setChoice;

        system("cls");

        MyRelation obj;
        obj.enterValues(setChoice);

        reflexive = obj.isReflexive();
        symmetric = obj.isSymmetric();
        antisymmetric = obj.isAntiSymmetric();
        transitive = obj.isTransitive();

        cout << "\tInformation\n";
        cout << "Relation...\n";
        obj.printRelation();
        cout << "\nReflexivity: " << boolalpha << reflexive;
        cout << "\nSymmetricity: " << symmetric;
        cout << "\nAnti-Symmetricity: " << antisymmetric;
        cout << "\nTransitivity: " << transitive;
        cout << "\nEquivalence: " << obj.isEquivalence(reflexive, symmetric, transitive);
        cout << "\nPartial Order Relation: " << obj.isPartial(reflexive, antisymmetric, transitive);

        temp = obj.refClosure();
        cout << "\n\nReflexive Closure of the Relation...\n";
        obj.printClosure(temp);

        temp = obj.symClosure();
        cout << "\nSymmetric Closure of the Relation...\n";
        obj.printClosure(temp);

        temp = obj.transClosure();
        cout << "\nTransitive Closure of the Relation...\n";
        obj.printClosure(temp);

        cout << "\nDo you want to operate more (Y/N): ";
        cin >> choice;
                
    } while (choice == 'Y' || choice == 'y');

    return 0;
}