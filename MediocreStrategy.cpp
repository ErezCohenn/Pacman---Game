#include "MediocreStrategy.h"
//-----------------------------------------------------------------------------------------------//
void MediocreStrategy::strategyMove(const Board& board, vector<Ghost>& ghosts, const Point& p_packman)
{
    if (RandomStrategy::getCountSteps() == (getAmountSameDir() * ghosts.size()))
    {
        SmartStrategy::setCountSteps(0);
        RandomStrategy::setCountSteps(0);
        amountSameSmartDir = (15 + rand() % 11); // change the amount steps of smart ghost
    }
    
    if (SmartStrategy::getCountSteps() < (amountSameSmartDir * ghosts.size()))
    {
        SmartStrategy::strategyMove(board, ghosts, p_packman);
    }
    else 
    {
        RandomStrategy::strategyMove(board, ghosts, p_packman);
    }
}
//-----------------------------------------------------------------------------------------------//