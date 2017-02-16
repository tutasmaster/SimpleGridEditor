#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

int mapTile[20][20] = {
    {0,0,1,0,0},
    {0,1,1,2,1},
    {1,0,2,2,1},
    {0,1,2,2,2},
    {2,2,2,0,0}
};
int mapTileA[20][20];
int usableBinds[10];

bool isServer;
class Tile{
public:
    int type;
    int x;
    int y;
};
int HEIGHT = 640;
int WIDTH = 640;

sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "Minecraft xD Tutas Edition");
class Mob{
public:
    int x;
    int y;
    short side;
    short sidey = 1;
    sf::RectangleShape animal;
    void updatePosition()
    {
        if(x > WIDTH-32){
            side = -1;
        }else if(x < 0){
            side = 1;
        }

        if(y > HEIGHT-32){
            sidey = -1;
        }else if(y < 0){
            sidey = 1;
        }

        x += side;
        y += sidey;

        animal.setPosition(sf::Vector2f(x,y));
        animal.setFillColor(sf::Color(255,255,255));
        app.draw(animal);
    }
};
std::vector<Mob> moblist;
void saveMap()
{
    std::ofstream saveFile;
    saveFile.open("Map.sav");
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            saveFile << mapTile[i][j] << "\n";
        }
    }
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            saveFile << mapTileA[i][j] << "\n";
        }
    }
    for(int i = 0; i < 10; i++){
        saveFile << usableBinds[i] << "\n";
    }
    saveFile.close();
}

bool loadMap()
{
    std::ifstream loadFile("Map.sav");
    if(!loadFile.is_open())
        return false;
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            std::string load;
            std::getline(loadFile,load);
            int loaded = atoi(load.c_str());
            mapTile[i][j] = loaded;
        }
    }

    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            std::string load;
            std::getline(loadFile,load);
            int loaded = atoi(load.c_str());
            mapTileA[i][j] = loaded;
        }
    }
    for(int j = 0; j < 10; j++)
    {
        std::string load;
        std::getline(loadFile,load);
        int loaded = atoi(load.c_str());
        usableBinds[j] = loaded;
    }


    loadFile.close();
    return true;
}



sf::Font font;

bool Menu = false;

int curB = 0;
int maxB = 256;
int curA = 0;

int plyx,plyy;

sf::Texture texGroup[10];

Tile totMap[20][20];


sf::Texture animalTexture;
void createMob()
{
    Mob current;
    current.x = 200;
    current.y = 200;
    current.side = -1;
    current.sidey = 1;
    current.animal.setSize(sf::Vector2f(32,32));
    current.animal.setTexture(&animalTexture);
    current.animal.setTextureRect(sf::IntRect(0,0,32,32));
    moblist.push_back(current);
}

void resetMap()
{
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            mapTile[i][j] = 0;
            mapTileA[i][j] = 0;
        }
    }
}

void drawBinds()
{
    sf::RectangleShape rect;
    rect.setTexture(&texGroup[0]);
    rect.setSize(sf::Vector2f(16,16));
    for(int i = 1; i < 11; i++)
    {
        if(i != 10){
            int til = usableBinds[i];
            int curC = til/15;
            int curD = til - 15*curC;
            rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
            rect.setFillColor(sf::Color(255,255,255));
            rect.setPosition(sf::Vector2f((i*16)+240,0));
        }else{
            int til = usableBinds[0];
            int curC = til/15;
            int curD = til - 15*curC;
            rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
            rect.setFillColor(sf::Color(255,255,255));
            rect.setPosition(sf::Vector2f((i*16)+240,0));
        }
        app.draw(rect);
    }

}

void drawMap()
{
    sf::RectangleShape rect;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            rect.setSize(sf::Vector2f(32,32));
            rect.setTexture(&texGroup[0]);
            rect.setPosition(sf::Vector2f(32*i,32*j));
            int til = mapTile[i][j];
            int curC = til/15;
            int curD = til - 15*curC;
            switch (til) {
                case 0: rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        break;
                case 53:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        break;
                case 37:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        break;
                case 49:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        break;
                case 50:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        break;
                case 72:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        break;
                default:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(255,255,255));
                        break;
            }
            app.draw(rect);
        }
    }
}

void drawMapA()
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(32,32));
    rect.setTexture(&texGroup[0]);
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            rect.setPosition(sf::Vector2f(32*i,32*j));
            int til = mapTileA[i][j];
            int curC = til/15;
            int curD = til - 15*curC;
            switch (til) {
                case 0: rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        rect.setSize(sf::Vector2f(32,32));
                        rect.setSize(sf::Vector2f(32,32));
                        break;
                case 53:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        rect.setSize(sf::Vector2f(32,32));
                        break;
                case 37:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        rect.setSize(sf::Vector2f(32,32));
                        break;
                case 49:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        rect.setSize(sf::Vector2f(32,32));
                        break;
                case 50:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        rect.setSize(sf::Vector2f(32,32));
                        break;
                case 72:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(94,157,52));
                        rect.setSize(sf::Vector2f(32,32));
                        break;
                case 76:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,32));
                        rect.setFillColor(sf::Color(255,255,255));
                        rect.setSize(sf::Vector2f(32,64));
                        break;
                case 77:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,32));
                        rect.setFillColor(sf::Color(255,255,255));
                        rect.setSize(sf::Vector2f(32,64));
                        break;
                default:rect.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
                        rect.setFillColor(sf::Color(255,255,255));
                        rect.setSize(sf::Vector2f(32,32));
                        break;
            }
            if(til != 0){
                app.draw(rect);
            }
        }
    }
}

int alph = 180;

void updateMenu()
{
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(32,32));
    block.setTexture(&texGroup[0]);
    for (int i = 0; i < 16; i++)
    {
    for (int j = 0; j < 16; j++)
        {
            block.setPosition(sf::Vector2f(32*i+64,32*j+64));
            block.setTextureRect(sf::IntRect(i*16,j*16,16,16));
            app.draw(block);
        }
    }
}

int main()
{
    /*char ans;
    cout<<"Do you want to open a server?"<<endl;
    cin>>ans;
    if(ans == 'y'){
        isServer = true;
    }else{
        isServer = false;
    }*/
    loadMap();
    sf::Image icon;
    if(icon.loadFromFile("mine.png")){
    app.setIcon(256,256,icon.getPixelsPtr());
    }
    font.loadFromFile("BRITANIC.ttf");
    sf::Text text;
    text.setCharacterSize(48);
    text.setFont(font);
    text.setPosition(sf::Vector2f(64,HEIGHT-64));
    // Create the main window
    app.setFramerateLimit(60);
    //createMob();
    // Load a sprite to display
    texGroup[0].loadFromFile("player.png");
    animalTexture.loadFromFile("animal.png");
    sf::RectangleShape rectA(sf::Vector2f(WIDTH,HEIGHT));
    rectA.setFillColor(sf::Color(0,0,0));
    sf::CircleShape ply(20,16);
    sf::RectangleShape rect(sf::Vector2f(80,80));
    rect.setPosition(sf::Vector2f(40,40));
    sf::RectangleShape look(sf::Vector2f(32,32));
    look.setFillColor(sf::Color(0,0,0,0));
    look.setOutlineColor(sf::Color(255,255,255));
    look.setOutlineThickness(1);
    ply.setFillColor(sf::Color(30,255,70,50));
    sf::RectangleShape gui(sf::Vector2f(64,64));
    gui.setFillColor(sf::Color(255,255,255,alph));
    gui.setTexture(&texGroup[0]);
    gui.setPosition(sf::Vector2f(0,HEIGHT-64));

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
            if (event.type == sf::Event::Resized)
            {
                HEIGHT = event.size.height;
                WIDTH = event.size.width;
            }
            if (event.type == sf::Event::MouseWheelScrolled && !Menu)
            {
                curB += event.mouseWheelScroll.delta;
                if(curB > maxB)
                    curB = maxB;
                if(curB < 0)
                    curB = 0;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::E){
                    Menu = !Menu;
                }
                if(event.key.code == sf::Keyboard::F1)
                {
                    saveMap();
                }
                if(event.key.code == sf::Keyboard::F2)
                {
                    loadMap();
                }
                if(event.key.code == sf::Keyboard::F3)
                {
                    resetMap();
                }
            }
            if  (event.type == sf::Event::MouseButtonPressed){
                if(Menu){
                    int sqx = sf::Mouse::getPosition(app).x / (WIDTH / 20);
                    int sqy = sf::Mouse::getPosition(app).y / (HEIGHT / 20);
                    sqx -= 2;
                    sqy -= 2;
                    if(sqx < 0)
                        sqx = 0;
                    if(sqx > 16)
                        sqx = 16;
                    if(sqy < 0)
                        sqy = 0;
                    if(sqy > 16)
                        sqy = 16;
                    curB = sqx + (sqy*15);
                }else{
                if(event.mouseButton.button == sf::Mouse::Middle)
                {
                    int sqx = sf::Mouse::getPosition(app).x / (WIDTH / 20);
                    int sqy = sf::Mouse::getPosition(app).y / (HEIGHT / 20);
                    if(mapTileA[sqx][sqy] != 0){
                        curB = mapTileA[sqx][sqy];
                    }else{
                        curB = mapTile[sqx][sqy];
                    }
                }
                }
            }
        }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
                curB = usableBinds[0];
            }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                curB = usableBinds[1];
            }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                curB = usableBinds[2];
            }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                curB = usableBinds[3];
            }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
                curB = usableBinds[4];
            }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
                curB = usableBinds[5];
            }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
                curB = usableBinds[6];
            }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
                curB = usableBinds[7];
            }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
                curB = usableBinds[8];
            }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
                curB = usableBinds[9];
            }
        }else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
                usableBinds[0] = curB;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                usableBinds[1] = curB;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                usableBinds[2] = curB;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                usableBinds[3] = curB;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
                usableBinds[4] = curB;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
                usableBinds[5] = curB;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
                usableBinds[6] = curB;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
                usableBinds[7] = curB;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
                usableBinds[8] = curB;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
                usableBinds[9] = curB;
            }
        }
        int sqx = sf::Mouse::getPosition(app).x / (WIDTH / 20);
        int sqy = sf::Mouse::getPosition(app).y / (HEIGHT / 20);

        int curC = curB/15;
        int curD = curB - 15*curC;
        gui.setTextureRect(sf::IntRect(curD*16,curC*16,16,16));
        switch (curB) {
            case 0: gui.setFillColor(sf::Color(94,157,52));
                    break;
            default:gui.setFillColor(sf::Color(255,255,255,alph));
                    break;
        }
        std::stringstream curText;
        curText << curB;
        text.setString(curText.str());int HEIGHT = 320;
        int WIDTH = 320;



        // Clear screen
        ply.setPosition(sf::Vector2f(sf::Mouse::getPosition(app).x-20,sf::Mouse::getPosition(app).y-20));
        if(!Menu){
        if(sqx < 0)
            sqx = 0;
        if(sqx > 19)
            sqx = 19;
        if(sqy < 0)
            sqy = 0;
        if(sqy > 19)
            sqy = 19;
        }else{
        if(sqx < 2)
            sqx = 2;
        if(sqx > 17)
            sqx = 17;
        if(sqy < 2)
            sqy = 2;
        if(sqy > 17)
            sqy = 17;
        }
        if(app.hasFocus() && !Menu){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    mapTile[sqx][sqy] = curB;
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    mapTileA[sqx][sqy] = curB;
        }
        look.setPosition(sqx*32,sqy*32);
        app.clear();
        if(!Menu){
        drawMap();
        drawMapA();
        for(unsigned int i = 0; i < moblist.size(); i++)
        {
            moblist[i].updatePosition();
        }
        app.draw(ply);
        }
        if(Menu)
            updateMenu();
        app.draw(gui);
        app.draw(text);
        app.draw(look);
        drawBinds();
        // Update the window
        app.display();
    }
    saveMap();
    return EXIT_SUCCESS;
}

