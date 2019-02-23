#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <sstream>
#include <string>

const int sizeM=1000;

//static max=1020
//dynamic max=1443
int lifecount=0;

using namespace std;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize,  int **tiles, unsigned int width,unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;
        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for ( int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
            {
                // get the current tile number
                int tileNumber = tiles[j][i];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);

                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


void GoL_rules(int maxi,int maxj, int **arr)
{
   // cout<<"test";
    srand(time(0));
    // int maxj=100;
    //int maxi=25;
    int **temp = new int*[sizeM];//объ€вление массива
    for (int count = 0; count < sizeM; count++)//выделение пам€ти под массив
        temp[count] = new int[sizeM];
    lifecount=0;

    //int temp[maxi][maxj];
    //cout<<"test";
    for (int i=0; i<maxi; i++)
    {
        for (int j=0; j<maxj; j++)
        {
            temp[i][j]=arr[i][j];
        }
    }
//copy (arr,temp);
//    temp=arr;
    for (int i=0; i<maxi; i++)
    {
        for (int j=0; j<maxj; j++)
        {
            int count =0;
            if (i>0 && i<maxi-1 && j>0 && j<maxj-1) // center
            {
                if (arr[i][j]==0)
                {


                    count=(arr[i-1][j-1]==1)+
                          (arr[i-1][j]==1)+
                          (arr[i-1][j+1]==1)+
                          (arr[i][j-1]==1)+
                          (arr[i][j+1]==1)+
                          (arr[i+1][j-1]==1)+
                          (arr[i+1][j]==1)+
                          (arr[i+1][j+1]==1);
                    int prob = rand()%10;
                    if(prob<count)
                        temp[i][j]=1;
                    else
                        temp[i][j]=arr[i][j];
                }
                else if (arr[i][j]==1)
                {
                    int prob = rand()%10;
                    if(prob<5)
                        temp[i][j]=2;
                }

            }
            // else
            //{
            if (i>0 && i<maxi-1 && j==0) // left side
            {
                if (arr[i][j]==0)
                {


                    count=(arr[i-1][maxj-1]==1)+
                          (arr[i-1][j]==1)+
                          (arr[i-1][j+1]==1)+
                          (arr[i][maxj-1]==1)+
                          (arr[i][j+1]==1)+
                          (arr[i+1][maxj-1]==1)+
                          (arr[i+1][j]==1)+
                          (arr[i+1][j+1]==1);
                    int prob = rand()%10;
                    if(prob<count)
                        temp[i][j]=1;
                    else
                        temp[i][j]=arr[i][j];
                }

                else  if (arr[i][j]==1)
                {
                    int prob = rand()%10;
                    if(prob<5)
                        temp[i][j]=2;
                }

            }
            // }


            if (i==0 && j>0 && j<maxj-1) //topside
            {
                if (arr[i][j]==0)
                {


                    count=(arr[maxi-1][j-1]==1)+
                          (arr[maxi-1][j]==1)+
                          (arr[maxi-1][j+1]==1)+
                          (arr[i][j-1]==1)+
                          (arr[i][j+1]==1)+
                          (arr[i+1][j-1]==1)+
                          (arr[i+1][j]==1)+
                          (arr[i+1][j+1]==1);
                    int prob = rand()%10;
                    if(prob<count)
                        temp[i][j]=1;
                    else
                        temp[i][j]=arr[i][j];
                }
                else if (arr[i][j]==1)
                {
                    int prob = rand()%10;
                    if(prob<5)
                        temp[i][j]=2;
                }


            }
            if (i==maxi-1 && j>0 && j<maxj-1) // bottom side
            {
                if (arr[i][j]==0)
                {
                    count=arr[i-1][j-1]+
                          arr[i-1][j]+
                          arr[i-1][j+1]+
                          arr[i][j-1]+
                          arr[i][j+1]+
                          arr[0][j-1]+
                          arr[0][j]+
                          arr[0][j+1];
                    int prob = rand()%10;
                    if(prob<count)
                        temp[i][j]=1;
                    else
                        temp[i][j]=arr[i][j];
                }
                else  if (arr[i][j]==1)
                {
                    int prob = rand()%10;
                    if(prob<5)
                        temp[i][j]=2;
                }

            }
            if (i>0 && i<maxi-1 && j==maxj-1) // right side
            {
                if (arr[i][j]==0)
                {


                    count=(arr[i-1][j-1]==1)+
                          (arr[i-1][j]==1)+
                          (arr[i-1][0]==1)+
                          (arr[i][j-1]==1)+
                          (arr[i][0]==1)+
                          (arr[i+1][j-1]==1)+
                          (arr[i+1][j])==1+
                          (arr[i+1][0]==1);
                    int prob = rand()%10;
                    if(prob<count)
                        temp[i][j]=1;
                    else
                        temp[i][j]=arr[i][j];
                }
                else  if (arr[i][j]==1)
                {
                    int prob = rand()%10;
                    if(prob<5)
                        temp[i][j]=2;
                }

            }
            if (i==0 && j==maxj-1) //top right
            {
                if (arr[i][j]==0)
                {
                    count=(arr[maxi-1][j-1]==1)+
                          (arr[maxi-1][j]==1)+
                          (arr[maxi-1][0]==1)+
                          (arr[i][j-1]==1)+
                          (arr[i][0]==1)+
                          (arr[i+1][j-1]==1)+
                          (arr[i+1][j]==1)+
                          (arr[i+1][j+1]==1);
                    int prob = rand()%10;
                    if(prob<count)
                        temp[i][j]=1;
                    else
                        temp[i][j]=arr[i][j];
                }
                else  if (arr[i][j]==1)
                {
                    int prob = rand()%10;
                    if(prob<5)
                        temp[i][j]=2;
                }

            }
            if (i==maxi-1 && j== maxj-1) // bottom right corner
            {
                if (arr[i][j]==0)
                {

                    count=(arr[i-1][j-1]==1)+
                          (arr[i-1][j]==1)+
                          (arr[i-1][0]==1)+
                          (arr[i][j-1]==1)+
                          (arr[i][0]==1)+
                          (arr[0][j-1]==1)+
                          (arr[0][j]==1)+
                          (arr[0][0]==1);
                    int prob = rand()%10;
                    if(prob<count)
                        temp[i][j]=1;
                    else
                        temp[i][j]=arr[i][j];
                }
                else if (arr[i][j]==1)
                {
                    int prob = rand()%10;
                    if(prob<5)
                        temp[i][j]=2;
                }


            }
            if (i==maxi-1 && j==0) // bottom left corner
            {
                if (arr[i][j]==0)
                {


                    count=(arr[i-1][maxj-1]==1)+
                          (arr[i-1][j]==1)+
                          (arr[i-1][j+1]==1)+
                          (arr[i][maxj-1]==1)+
                          (arr[i][j+1]==1)+
                          (arr[0][maxj-1]==1)+
                          (arr[0][j]==1)+
                          (arr[0][j+1]==1);
                    int prob = rand()%10;
                    if(prob<count)
                        temp[i][j]=1;
                    else
                        temp[i][j]=arr[i][j];
                }
                else  if (arr[i][j]==1)
                {
                    int prob = rand()%10;
                    if(prob<5)
                        temp[i][j]=2;
                }

            }
            if (i==0 && j==0) // top left corner
            {
                if (arr[i][j]==0)
                {


                    count=(arr[maxi-1][maxj-1]==1)+
                          (arr[maxi-1][j]==1)+
                          (arr[maxi-1][j+1]==1)+
                          (arr[i][maxj-1]==1)+
                          (arr[i][j+1]==1)+
                          (arr[i+1][maxj-1]==1)+
                          (arr[i+1][j]==1)+
                          (arr[i+1][j+1]==1);
                    int prob = rand()%10;
                    if(prob<count)
                        temp[i][j]=1;
                    else
                        temp[i][j]=arr[i][j];
                }
                else if (arr[i][j]==1)
                {
                    int prob = rand()%10;
                    if(prob<5)
                        temp[i][j]=2;
                }

            }

            if (temp[i][j]==0)
                lifecount++;
        }

    }
    for (int i=0; i<maxi; i++)
    {
        for (int j=0; j<maxj; j++)
        {
            arr[i][j]=temp[i][j];
        }
    }
    for (int count = 0; count < sizeM; count++)
        delete [] temp[count];

    delete [] temp;
}
int main()
{
    srand(time(0));
    long long gen=0;
    int **field = new int*[sizeM];//объ€вление массива
    for (int count = 0; count < sizeM; count++)//выделение пам€ти под массив
        field[count] = new int[sizeM];
    for(long long i=0; i<sizeM; i++)
        for (long long j=0; j<sizeM; j++)
        {
            field[i][j]=rand()%2;
            // field[i][j]=0;
            if (field[i][j]==0)
                lifecount++;
        }
/*
        for (int j=240;j<sizeM;j++)
        {
            field [80][j]=1;
            field [100][j]=1;
            field [130][j]=1;
            field [163][j]=1;
            field [193][j]=1;
            field [203][j]=1;
            field [240][j]=1;
            field [287][j]=1;
            field [300][j]=1;
            field [323][j]=1;
            field [333][j]=1;
        }
        for (int i=70;i<340;i++)
            for (int j=140;j<240;j++)
            field[i][j]=1;
*/
    /*
            while (1)
            {
                cout<<"Generation: " <<gen<<" Amount of cells alive:"<< lifecount<<endl;

                for (int i=0; i<sizeM; i++)
                {

                    for (int j=0; j<sizeM; j++)
                    {
                        if (field[i][j]==0)
                        {
                            cout<<"0";
                        }
                        if (field[i][j]==1)
                        {
                            cout<<"1";
                        }
                        if (field[i][j]==2)
                        {
                            cout<<"2";
                        }

                    }
                    cout<<endl;

                }
                GoL_rules(sizeM,sizeM,field);
                gen++;
                getch();
                system("cls");

            }
    */
    sf::RenderWindow window(sf::VideoMode(sizeM, sizeM), "Tilemap");
    sf::Font font;
    if (!font.loadFromFile("ArcadeClassic.ttf"))
    {
        cout<<"Font load error";
    }
    sf::Text text;
    text.setFont(font);
    //text.setString("Generation ");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    clock_t begin,end;
    double timespent;
    TileMap map;
    if (!map.load("texpack.png", sf::Vector2u(1, 1), field, sizeM, sizeM))
        return -1;

    while (window.isOpen())
    {
        begin=clock();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
       // if( sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            // if (lifecount!=0)
        {
            if (!map.load("texpack.png", sf::Vector2u(1, 1), field, sizeM, sizeM))
                return -1;
            GoL_rules(sizeM,sizeM,field);
            gen++;
            std::ostringstream ost;
            ost << gen;
            std::string gen_str = ost.str();
            std::ostringstream lcss;
            lcss<<lifecount;
            std:: string lifecount_str=lcss.str();
            text.setString( "Turn "+gen_str+"    Trees alive "+lifecount_str);
            //cout<<"Turn: " <<gen<<" Amount of Trees alive:"<< lifecount<<endl;

        }
        //if (lifecount==0)
        /*
            else
            {
                std::ostringstream ost;
                ost << gen;
                std::string gen_str = ost.str();
                text.setCharacterSize(20);
                text.setString( "Game over  All cells are dead Final generation  "+ gen_str);
            }
            */
        window.clear();
        window.draw(map);
        window.draw(text);
        window.display();
        end=clock();
        timespent=(double)(end-begin)/ CLOCKS_PER_SEC;
        cout<<1/timespent<<endl;
    }

    for (int count = 0; count < sizeM; count++)
        delete [] field[count];

    delete [] field;
    return 0;
}
