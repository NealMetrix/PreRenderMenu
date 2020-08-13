#pragma once
#include"Debug.h"

class verticyBuffer;

static const unsigned int elementsQ = 9;
const std::string actionsList[elementsQ] = 
{
    "createvertex","color","delete","display","draworder","generate","help","quit","reorder"
};
/*A bunch of const values to use across all functions to define what index each element is to make reordering them
much more convenient*/
/*This would probably be better as an array*/
const unsigned int createV = 0;
const unsigned int colorV = 1;
const unsigned int deleteV = 2;
const unsigned int displayV = 3;
const unsigned int draworder = 4;
const unsigned int generateV = 5;
const unsigned int helpV = 6;
const unsigned int quitV = 7;
const unsigned int reorderV = 8;

static void createVertex(verticyBuffer& v)
{
    float inputX = 0;
    float inputY = 0;
    std::cout << "Enter Coordinate x: ";
    std::cin >> inputX;

    std::cout << "Enter Coordinate y: ";
    std::cin >> inputY;
    
    v.addVertex(inputX, inputY);

    std::cout << std::endl;

    return;
}
static void deleteLastVector(verticyBuffer& v)
{

    /*Handeling the exception when you delete a vertex and then never change the order by clearing it so the order doesn't
    try and access an element of the verticies vector that has already been deleted.*/
    if (v.getVerticiesSize() <= v.order.size())
    {
        v.clearOrder();
        std::cout << "Order exceeded vertex value. Order cleared..." << std::endl;
    }
    v.deleteVertex();
    v.displayVerticies();
}
static void help()
{
    /*If I created a struct for this and then used a for loop to cycle through indexes I could make them appear in alphabetical order
    no matter what order I put them in. This way I might not have to keep reorganizing the list*/
    std::cout << actionsList[createV] << "\tAsks for x and y positions of a new vertex" << std::endl;//createvertex
    std::cout << actionsList[colorV] << "\t\tSets the color of the shape drawn. Is white by default" << std::endl;//setcolor
    std::cout << actionsList[deleteV] << "\t\tDeletes the last vertex typed" << std::endl;//delete
    std::cout << actionsList[displayV] << "\t\tDisplays all current verticies of the shape" << std::endl;//displayverticies
    std::cout << actionsList[draworder] << "\tDisplays the verticies in the order they are used to draw a shape" << std::endl;
    std::cout << actionsList[generateV] << "\tGenerates the shape" << std::endl;//generate
    std::cout << actionsList[helpV] << "\t\tDisplays all possible actions and what they do" << std::endl;//help
    std::cout << actionsList[quitV] << "\t\tExits the program without generating a shape" << std::endl;//quit
    std::cout << actionsList[reorderV] << "\t\tReorders the way that the verticies are drawn by specifying the vertex number in different ordrers" << std::endl;//reorder
}

/*Allowing the user to reorganize in what order the verticies are drawn.*/
static void reorder(verticyBuffer& pushto)
{
    pushto.clearOrder();
    unsigned int orderInput = 1;
    std::cout << "Asking for vertex number until 0 is found" << std::endl;
    std::cout << "Strings are invalid at this point" << std::endl;
    std::cin >> orderInput;
    while(orderInput!=0)
    {
        /*Making sure you can't enter a greater verticy number than you have verticies*/
        if (orderInput >= pushto.getVerticiesSize()+1)
        {
            std::cout << "Error max vertex exceeded... Deordering verticies" << std::endl;
            pushto.clearOrder();
            return;
        }
        pushto.order.push_back(orderInput-1);/*We push elements back to the order vector*/
        std::cin >> orderInput;
    }
    std::cout << std::endl << std::endl;
}
/*Checking for different actions*/
static unsigned int action(std::string& entry, verticyBuffer& verticies)
{
    unsigned int index = 0;
    while (actionsList[index] != entry && index < sizeof(actionsList[elementsQ]))
    {
        index++;
    }

    switch (index)
    {
    case createV:
        createVertex(verticies);
        break;
    case deleteV:
        deleteLastVector(verticies);
        break;
    case displayV:
        verticies.displayVerticies();
        break;
    case draworder:
        verticies.drawOrder();
        break;
    case generateV:
        std::cout << "Generating..." << std::endl;
        break;
    case helpV:
        help();
        break;
    case reorderV:
        reorder(verticies);
        break;
    default:
        std::cout << "Action is undefined" << std::endl;
    }
    std::cout<<std::endl;

    return index;/*In case we want to check the final value of i*/
}