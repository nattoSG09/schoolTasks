#pragma once
#include "Stage.h"

class Memento
{
private:
	friend class Stage;
	BlockData state_[XSIZE][ZSIZE];

    //コンストラクタ
    Memento(const BlockData _table[XSIZE][ZSIZE]) {
        for (int x = 0; x < XSIZE; ++x) 
            for (int y = 0; y < ZSIZE; ++y) 
                state_[x][y] = _table[x][y];
    }

    BlockData GetState(int x, int z) const {
        return state_[x][z];
    }

    void SetState(const BlockData newState[XSIZE][ZSIZE]) {
        for (int x = 0; x < XSIZE; ++x) {
            for (int y = 0; y < ZSIZE; ++y) {
                state_[x][y] = newState[x][y];
            }
        }
    }
public:
    ~Memento() {}
};

