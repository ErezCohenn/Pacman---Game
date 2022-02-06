#include "RandomStrategy.h"
//-----------------------------------------------------------------------------------------------//
void RandomStrategy::strategyMove(const Board& board, vector<Ghost>& ghosts, const Point& p_packman)
{
    unsigned int i = 0;
    Point nextStep;

    while (i < ghosts.size())
    {
        if (countSteps == amountSameDir * ghosts.size()) // change direciton after amountSameDir steps
        {
            countSteps = 0;
        }


        if (countSteps >= 0 && countSteps < ghosts.size())
        {
            ghosts[i].setDirection(rand() % 4);
        }

        nextStep = ghosts[i].getCurr() + ghosts[i].getDirection();
      
        if (board.isValidMove(nextStep))
        {
            ghosts[i].move(nextStep); // move creature
            
            countSteps++;
            i++;
        }
        else
        {
            ghosts[i].setDirection(rand() % 4);
        }
    }

    
 }
//-----------------------------------------------------------------------------------------------//