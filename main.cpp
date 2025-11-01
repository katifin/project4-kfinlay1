//
// Kathryn Finlayson
// Project 1
// CS 2240C
//

#include "Pokemon.h"
#include <vector>
#include "sorting-algorithms/bubbleSort.h"
#include "sorting-algorithms/heapSort.h"
#include "sorting-algorithms/insertionSort.h"
#include "sorting-algorithms/mergeSort.h"
#include "sorting-algorithms/radixSort.h"
#include "sorting-algorithms/selectionSort.h"
#include "stability-test/contactsList.h"
#include <iomanip>
using namespace std;

void stabilityTest();

int main() {
    vector<Pokemon> pokemon;

    if (getDataFromFile(pokemon)) {
        // cout << "File read. Size of vector: " << pokemon.size() << endl;
        ofstream readsOut;
        readsOut.open("../data/sort_reads.csv");
        ofstream allocatesOut;
        allocatesOut.open("../data/sort_allocates.csv");

        readsOut << "Size,Bubble,Merge,Heap,Selection,Insertion" << endl;
        allocatesOut << "Size,Bubble,Merge,Heap,Selection,Insertion" << endl;

        for (int i = 1000; i > 0; i -= 100) {
            vector<Pokemon> pokemonResized = pokemon;
            pokemonResized.resize(i);
            readsOut << i << ", ";
            allocatesOut << i << ", ";

            unsigned long reads = 0;
            unsigned long allocations = 0;
            vector<Pokemon> bubbleSorted = bubbleSort(pokemonResized, reads, allocations);
            // cout << "Bubble, " << i << " - Reads: " << reads << ", Allocated Memory: " << allocations << endl;
            readsOut << reads << ", ";
            allocatesOut << allocations << ", ";

            reads = 0;
            allocations = 0;
            vector<Pokemon> mergeSorted = mergeSort(pokemonResized, reads, allocations);
            // cout << "Merge " << i << " - Reads: " << reads << ", Allocated Memory: " << allocations << endl;
            readsOut << reads << ", ";
            allocatesOut << allocations << ", ";

            reads = 0;
            allocations = 0;
            vector<Pokemon> heapSorted = heapSort(pokemonResized, reads, allocations);
            // cout << "Heap " << i << " - Reads: " << reads << ", Allocated Memory: " << allocations << endl;
            readsOut << reads << ", ";
            allocatesOut << allocations << ", ";

            reads = 0;
            allocations = 0;
            vector<Pokemon> selectionSorted = selectionSort(pokemonResized, reads, allocations);
            // cout << "Selection " << i << " - Reads: " << reads << ", Allocated Memory: " << allocations << endl;
            readsOut << reads << ", ";
            allocatesOut << allocations << ", ";

            reads = 0;
            allocations = 0;
            vector<Pokemon> insertionSorted = insertionSort(pokemonResized, reads, allocations);
            // cout << "Insertion " << i << " - Reads: " << reads << ", Allocated Memory: " << allocations << endl;
            readsOut << reads << endl;
            allocatesOut << allocations << endl;
        }
        readsOut.close();
        allocatesOut.close();
    }

    stabilityTest();
    return 0;
}

void stabilityTest() {
    ContactsList people;
    people.readContactsFromFile("../stability-test/names.csv");
    cout << "People (Default ordering)" << endl;
    people.printList();

    cout << endl << "Bubble Sort" << endl;
    people.sortAndPrint(bubbleSort<contact>);

    cout << endl << "Merge Sort" << endl;
    people.sortAndPrint(mergeSort<contact>);

    cout << endl << "Heap Sort" << endl;
    people.sortAndPrint(heapSort<contact>);

    cout << endl << "Selection Sort" << endl;
    people.sortAndPrint(selectionSort<contact>);

    cout << endl << "Insertion Sort" << endl;
    people.sortAndPrint(insertionSort<contact>);
}