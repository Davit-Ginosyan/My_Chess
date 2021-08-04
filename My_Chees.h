#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum piece
{
  King,
  Queen,
  Bishop,
  Knight,
  Rook,
  Pawn,
  Empty
};
enum color
{
  White,
  Black,
  None
};

class Square
{
private:
  piece pic;
  color col;

public:
  void set_piece_and_color(piece pic, color col)
  {
    this->pic = pic;
    this->col = col;
  }
  piece get_piece() { return this->pic; }
  color get_color() { return this->col; }
  int count = 0;
  int current = 0;
};

class Board : public Square
{
private:
  Square square[8][8];
  vector<string> piece_white;
  vector<string> piece_black;
  vector<pair<int, int>> index_check;
  int black_king_cordinate_1 = 7;
  int black_king_cordinate_2 = 4;
  int white_king_cordinate_1 = 0;
  int white_king_cordinate_2 = 4;
  bool mate_white = 0;
  bool mate_black = 0;

public:
  Board();
  void print();
  void start();
  bool pawn(int, int, int, int, color);
  bool bishop(int, int, int, int, color);
  bool rook(int, int, int, int, color);
  bool knight(int, int, int, int, color);
  bool queen(int, int, int, int, color);
  bool king(int, int, int, int, color);
  bool legal_move(int, int, int, int, color, piece);
  void taken_pieces(piece, color);
  bool check_white();
  bool check_black();
  void check_bishop_cordinate(int, int, int, int);
  void check_rook_cordinate(int, int, int, int);
  void check_queen_cordinate(int, int, int, int);
  void mate();
};

Board::Board()
{
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      square[i][j].set_piece_and_color(Empty, None);
    }
  }
  for (int i = 0; i < 8; ++i)
  {
    square[1][i].set_piece_and_color(Pawn, White);
    square[6][i].set_piece_and_color(Pawn, Black);
  }
  square[0][0].set_piece_and_color(Rook, White);
  square[0][7].set_piece_and_color(Rook, White);
  square[0][1].set_piece_and_color(Knight, White);
  square[0][6].set_piece_and_color(Knight, White);
  square[0][2].set_piece_and_color(Bishop, White);
  square[0][5].set_piece_and_color(Bishop, White);
  square[0][3].set_piece_and_color(Queen, White);
  square[0][4].set_piece_and_color(King, White);
  square[7][0].set_piece_and_color(Rook, Black);
  square[7][7].set_piece_and_color(Rook, Black);
  square[7][1].set_piece_and_color(Knight, Black);
  square[7][6].set_piece_and_color(Knight, Black);
  square[7][2].set_piece_and_color(Bishop, Black);
  square[7][5].set_piece_and_color(Bishop, Black);
  square[7][3].set_piece_and_color(Queen, Black);
  square[7][4].set_piece_and_color(King, Black);
  this->print();
}

void Board::print()

{
  char ch[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  char ch_2[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
  string ch_1 = "  ";

  cout << " ";
  for (int k = 0; k < 8; ++k)
  {
    cout << "  " << ch[k] << " ";
  }

  cout << '\t';
  for (int i = 0; i < piece_black.size(); ++i)
  {
    cout << piece_black[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < 8; ++i)
  {
    cout << "----------------------------------" << endl;
    cout << ch_2[i] << "| ";
    for (int j = 0; j < 8; ++j)
    {
      piece pic = square[i][j].get_piece();
      color col = square[i][j].get_color();

      switch (pic)
      {
      case King:
        if (col == White)
        {
          cout << "\u2654"
               << " | ";
        }
        else
        {
          cout << "\u265A"
               << " | ";
        }
        break;
      case Queen:
        if (col == White)
        {
          cout << "\u2655"
               << " | ";
        }
        else
        {
          cout << "\u265B"
               << " | ";
        }
        break;
      case Rook:
        if (col == White)
        {
          cout << "\u2656"
               << " | ";
        }
        else
        {
          cout << "\u265C"
               << " | ";
        }
        break;
      case Knight:
        if (col == White)
        {
          cout << "\u2658"
               << " | ";
        }
        else
        {
          cout << "\u265E"
               << " | ";
        }
        break;
      case Bishop:
        if (col == White)
        {
          cout << "\u2657"
               << " | ";
        }
        else
        {
          cout << "\u265D"
               << " | ";
        }
        break;
      case Pawn:
        if (col == White)
        {
          cout << "\u2659"
               << " | ";
        }
        else
        {
          cout << "\u265F"
               << " | ";
        }
        break;
      case Empty:
        if (col == None)
        {
          cout << "  | ";
        }
        break;
      default:
        break;
      }
    }
    cout << ch_2[i] << endl;
  }
  cout << "----------------------------------" << endl;
  cout << " ";
  for (int k = 0; k < 8; ++k)
  {
    cout << "  " << ch[k] << " ";
  }
  cout << '\t';
  for (int i = 0; i < piece_white.size(); ++i)
  {
    cout << piece_white[i] << " ";
  }
  cout << endl;
}

bool Board::pawn(int x, int y, int x_1, int y_1, color col)
{
  if (col == White && square[x_1][y_1].get_color() != White)
  {
    if (x == 1 && (x_1 - x == 2))
    {
      if (y_1 - y == 0 && (square[x_1][y_1].get_color() == None))
      {
        return true;
      }
    }
    else if (x_1 - x == 1)
    {
      if (y_1 - y == 0 && square[x_1][y_1].get_color() == None)
      {
        return true;
      }
      if ((y_1 - y == 1 || y_1 - y == -1) && square[x_1][y_1].get_color() == Black)
      {
        taken_pieces(square[x_1][y_1].get_piece(), Black);
        return true;
      }
    }
  }
  if (col == Black && (square[x_1][y_1].get_color() != Black))
  {
    if (x == 6 && (x - x_1 == 2))
    {
      if (y - y_1 == 0 && square[x_1][y_1].get_color() == None)
      {
        return true;
      }
    }
    else if (x - x_1 == 1)
    {
      if (y - y_1 == 0 && square[x_1][y_1].get_color() == None)
      {
        return true;
      }
      if ((y - y_1 == 1 || y - y_1 == -1) && (square[x_1][y_1].get_color() == White))
      {
        taken_pieces(square[x_1][y_1].get_piece(), White);
        return true;
      }
    }
  }
  return false;
}

bool Board::bishop(int x, int y, int x_1, int y_1, color col)
{
  for (int i = 1; i < 8; ++i)
  {
    if (((x - x_1 == i) || (x - x_1 == -i)) && ((y - y_1 == i) || (y - y_1 == -i)))
    {
      if ((x < x_1) && (y < y_1))
      {
        int temp = x;
        int temp_1 = x_1 - 1;
        while (temp_1 != temp)
        {
          ++temp;
          ++x;
          ++y;
          if (square[x][y].get_color() != None)
          {
            return false;
          }
        }
        if (square[x_1][y_1].get_color() != col)
        {
          if (square[x_1][y_1].get_color() == White)
          {
            taken_pieces(square[x_1][y_1].get_piece(), White);
          }
          if (square[x_1][y_1].get_color() == Black)
          {
            taken_pieces(square[x_1][y_1].get_piece(), Black);
          }

          return true;
        }
      }
      if ((x > x_1) && (y > y_1))
      {
        int temp = x;
        int temp_1 = x_1 + 1;
        while (temp != temp_1)
        {
          ++temp_1;
          --x;
          --y;
          if (square[x][y].get_color() != None)
          {
            return false;
          }
        }
        if (square[x_1][y_1].get_color() != col)
        {
          if (square[x_1][y_1].get_color() == White)
          {
            taken_pieces(square[x_1][y_1].get_piece(), White);
          }
          if (square[x_1][y_1].get_color() == Black)
          {
            taken_pieces(square[x_1][y_1].get_piece(), Black);
          }
          return true;
        }
      }
      if ((x < x_1) && (y > y_1))
      {
        int temp = x;
        int temp_1 = x_1 - 1;
        while (temp_1 != temp)
        {
          ++temp;
          ++x;
          --y;
          if (square[x][y].get_color() != None)
          {
            return false;
          }
        }
        if (square[x_1][y_1].get_color() != col)
        {
          if (square[x_1][y_1].get_color() == White)
          {
            taken_pieces(square[x_1][y_1].get_piece(), White);
          }
          if (square[x_1][y_1].get_color() == Black)
          {
            taken_pieces(square[x_1][y_1].get_piece(), Black);
          }
          return true;
        }
      }
      if ((x > x_1) && (y < y_1))
      {
        int temp = x;
        int temp_1 = x_1 + 1;
        while (temp_1 != temp)
        {
          ++temp_1;
          --x;
          ++y;
          if (square[x][y].get_color() != None)
          {
            return false;
          }
        }
        if (square[x_1][y_1].get_color() != col)
        {
          if (square[x_1][y_1].get_color() == White)
          {
            taken_pieces(square[x_1][y_1].get_piece(), White);
          }
          if (square[x_1][y_1].get_color() == Black)
          {
            taken_pieces(square[x_1][y_1].get_piece(), Black);
          }
          return true;
        }
      }
    }
  }
  return false;
}

bool Board::rook(int x, int y, int x_1, int y_1, color col)
{
  if (x == x_1 && y > y_1)
  {
    while (y != y_1 + 1)
    {
      --y;
      if (square[x][y].get_color() != None)
      {
        return false;
      }
    }
    if (square[x_1][y_1].get_color() != col)
    {
      if (square[x_1][y_1].get_color() == White)
      {
        taken_pieces(square[x_1][y_1].get_piece(), White);
      }
      if (square[x_1][y_1].get_color() == Black)
      {
        taken_pieces(square[x_1][y_1].get_piece(), Black);
      }
      return true;
    }
  }
  if (x == x_1 && y < y_1)
  {
    while (y != y_1 - 1)
    {
      ++y;
      if (square[x][y].get_color() != None)
      {
        return false;
      }
    }
    if (square[x_1][y_1].get_color() != col)
    {
      if (square[x_1][y_1].get_color() == White)
      {
        taken_pieces(square[x_1][y_1].get_piece(), White);
      }
      if (square[x_1][y_1].get_color() == Black)
      {
        taken_pieces(square[x_1][y_1].get_piece(), Black);
      }
      return true;
    }
  }
  if (y == y_1 && x > x_1)
  {
    while (x != x_1 + 1)
    {
      --x;
      if (square[x][y].get_color() != None)
      {
        return false;
      }
    }
    if (square[x_1][y_1].get_color() != col)
    {
      if (square[x_1][y_1].get_color() == White)
      {
        taken_pieces(square[x_1][y_1].get_piece(), White);
      }
      if (square[x_1][y_1].get_color() == Black)
      {
        taken_pieces(square[x_1][y_1].get_piece(), Black);
      }
      return true;
    }
  }
  if (y == y_1 && x < x_1)
  {
    while (x != x_1 - 1)
    {
      ++x;
      if (square[x][y].get_color() != None)
      {
        return false;
      }
    }
    if (square[x_1][y_1].get_color() != col)
    {
      if (square[x_1][y_1].get_color() == White)
      {
        taken_pieces(square[x_1][y_1].get_piece(), White);
      }
      if (square[x_1][y_1].get_color() == Black)
      {
        taken_pieces(square[x_1][y_1].get_piece(), Black);
      }
      return true;
    }
  }
  return false;
}

bool Board::knight(int x, int y, int x_1, int y_1, color col)
{
  if (((y == y_1 - 1 || y == y_1 + 1) && (x == x_1 - 2 || x == x_1 + 2)) ||
      ((y == y_1 - 2 || y == y_1 + 2) && (x == x_1 - 1 || x == x_1 + 1)))
  {
    if (square[x_1][y_1].get_color() != col)
    {
      if (square[x_1][y_1].get_color() == White)
      {
        taken_pieces(square[x_1][y_1].get_piece(), White);
      }
      if (square[x_1][y_1].get_color() == Black)
      {
        taken_pieces(square[x_1][y_1].get_piece(), Black);
      }
      return true;
    }
  }
  return false;
}

bool Board::queen(int x, int y, int x_1, int y_1, color col)
{
  if (bishop(x, y, x_1, y_1, col) || rook(x, y, x_1, y_1, col))
  {
    return true;
  }
  return false;
}

bool Board::king(int x, int y, int x_1, int y_1, color col)
{

  if ((x - x_1 == 0 || x - x_1 == -1 || x - x_1 == 1) && (y - y_1 == 0 || y - y_1 == 1 || y - y_1 == -1))
  {
    if (square[x_1][y_1].get_color() != col)
    {
      if (square[x_1][y_1].get_color() == White)
      {
        taken_pieces(square[x_1][y_1].get_piece(), White);
        return true;
      }
      if (square[x_1][y_1].get_color() == Black)
      {
        taken_pieces(square[x_1][y_1].get_piece(), Black);
        return true;
      }
      return true;
    }
  }

  return false;
}

bool Board::legal_move(int x_1, int y_1, int x_2, int y_2, color col, piece pic)
{
  switch (pic)
  {
  case King:
    if (col == Black)
    {
      if (x_1 == 7 && y_1 == 4 && x_2 == 7 && y_2 == 6 && square[7][4].count == 0)
      {
        if (square[7][5].get_color() == None &&
            square[7][6].get_color() == None &&
            square[7][7].count == 0)
        {
          square[x_2][y_2].set_piece_and_color(King, Black);
          square[x_1][y_1].set_piece_and_color(Empty, None);
          square[7][5].set_piece_and_color(Rook, Black);
          square[7][7].set_piece_and_color(Empty, None);
          square[x_1][y_1].count++;
          square[7][7].count++;
          black_king_cordinate_1 = x_2;
          black_king_cordinate_2 = y_2;
          return true;
        }
      }
      if (x_1 == 7 && y_1 == 4 && x_2 == 7 && y_2 == 2 && square[7][4].count == 0)
      {
        if (square[7][3].get_color() == None &&
            square[7][2].get_color() == None &&
            square[7][1].get_color() == None &&
            square[7][0].count == 0)
        {
          square[x_2][y_2].set_piece_and_color(King, Black);
          square[x_1][y_1].set_piece_and_color(Empty, None);
          square[7][3].set_piece_and_color(Rook, Black);
          square[7][0].set_piece_and_color(Empty, None);
          square[x_1][y_1].count++;
          square[7][0].count++;
          black_king_cordinate_1 = x_2;
          black_king_cordinate_2 = y_2;
          return true;
        }
      }
      else if (king(x_1, y_1, x_2, y_2, col))
      {
        for (int i = 0; i < index_check.size(); ++i)
        {
          if (x_2 == index_check[i].first && y_2 == index_check[i].second)
          {
            return false;
          }
        }
        square[x_2][y_2].set_piece_and_color(King, Black);
        square[x_1][y_1].set_piece_and_color(Empty, None);
        square[x_1][y_1].count++;
        black_king_cordinate_1 = x_2;
        black_king_cordinate_2 = y_2;
        return true;
      }
      return false;
    }

    else
    {
      if (x_1 == 0 && y_1 == 4 && x_2 == 0 && y_2 == 6 && square[0][4].count == 0)
      {
        if (square[0][5].get_color() == None &&
            square[0][6].get_color() == None &&
            square[0][7].count == 0)
        {
          square[x_2][y_2].set_piece_and_color(King, White);
          square[x_1][y_1].set_piece_and_color(Empty, None);
          square[0][5].set_piece_and_color(Rook, White);
          square[0][7].set_piece_and_color(Empty, None);
          square[x_1][y_1].count++;
          square[0][7].count++;
          white_king_cordinate_1 = x_2;
          white_king_cordinate_2 = y_2;
          return true;
        }
      }
      if (x_1 == 0 && y_1 == 4 && x_2 == 0 && y_2 == 2 && square[0][4].count == 0)
      {
        if (square[0][3].get_color() == None &&
            square[0][2].get_color() == None &&
            square[0][1].get_color() == None &&
            square[0][0].count == 0)
        {
          square[x_2][y_2].set_piece_and_color(King, White);
          square[x_1][y_1].set_piece_and_color(Empty, None);
          square[0][3].set_piece_and_color(Rook, White);
          square[0][0].set_piece_and_color(Empty, None);
          square[x_1][y_1].count++;
          square[0][0].count++;
          white_king_cordinate_1 = x_2;
          white_king_cordinate_2 = y_2;
          return true;
        }
      }
      else if (king(x_1, y_1, x_2, y_2, col))
      {
        for (int i = 0; i < index_check.size(); ++i)
        {
          if (x_2 == index_check[i].first && y_2 == index_check[i].second)
          {
            return false;
          }
        }
        square[x_2][y_2].set_piece_and_color(King, White);
        square[x_1][y_1].set_piece_and_color(Empty, None);
        square[x_1][y_1].count++;
        white_king_cordinate_1 = x_2;
        white_king_cordinate_2 = y_2;
        return true;
      }
      return false;
    }

  case Queen:
    if (col == White)
    {
      if (queen(x_1, y_1, x_2, y_2, col))
      {
        Square tmp;
        tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
        square[x_2][y_2].set_piece_and_color(Queen, White);
        square[x_1][y_1].set_piece_and_color(Empty, None);
        square[x_1][y_1].count++;
        if (check_white())
        {
          square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
          square[x_1][y_1].set_piece_and_color(Queen, White);
          square[x_1][y_1].count--;
          if (square[x_2][y_2].get_piece() != Empty)
          {
            piece_black.pop_back();
          }
          return false;
        }
        return true;
      }
      return false;
    }
    else if (queen(x_1, y_1, x_2, y_2, col))
    {
      Square tmp;
      tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
      square[x_2][y_2].set_piece_and_color(Queen, Black);
      square[x_1][y_1].set_piece_and_color(Empty, None);
      square[x_1][y_1].count++;
      if (check_black())
      {
        square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
        square[x_1][y_1].set_piece_and_color(Queen, Black);
        square[x_1][y_1].count--;
        if (square[x_2][y_2].get_piece() != Empty)
        {
          piece_white.pop_back();
        }
        return false;
      }
      return true;
    }
    return false;
  case Rook:
    if (col == White)
    {
      if (rook(x_1, y_1, x_2, y_2, col))
      {
        Square tmp;
        tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
        square[x_2][y_2].set_piece_and_color(Rook, White);
        square[x_1][y_1].set_piece_and_color(Empty, None);
        square[x_1][y_1].count++;
        if (check_white())
        {
          square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
          square[x_1][y_1].set_piece_and_color(Rook, White);
          square[x_1][y_1].count--;
          if (square[x_2][y_2].get_piece() != Empty)
          {
            piece_black.pop_back();
          }
          return false;
        }
        return true;
      }
      return false;
    }
    else if (rook(x_1, y_1, x_2, y_2, col))
    {
      Square tmp;
      tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
      square[x_2][y_2].set_piece_and_color(Rook, Black);
      square[x_1][y_1].set_piece_and_color(Empty, None);
      square[x_1][y_1].count++;
      if (check_black())
      {
        square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
        square[x_1][y_1].set_piece_and_color(Rook, Black);
        square[x_1][y_1].count--;
        if (square[x_2][y_2].get_piece() != Empty)
        {
          piece_white.pop_back();
        }
        return false;
      }
      return true;
    }
    return false;

  case Knight:
    if (col == White)
    {
      if (knight(x_1, y_1, x_2, y_2, col))
      {
        Square tmp;
        tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
        square[x_2][y_2].set_piece_and_color(Knight, White);
        square[x_1][y_1].set_piece_and_color(Empty, None);
        square[x_1][y_1].count++;
        if (check_white())
        {
          square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
          square[x_1][y_1].set_piece_and_color(Knight, White);
          square[x_1][y_1].count--;
          if (square[x_2][y_2].get_piece() != Empty)
          {
            piece_black.pop_back();
          }
          return false;
        }
        return true;
      }
      return false;
    }
    else if (knight(x_1, y_1, x_2, y_2, col))
    {
      Square tmp;
      tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
      square[x_2][y_2].set_piece_and_color(Knight, Black);
      square[x_1][y_1].set_piece_and_color(Empty, None);
      square[x_1][y_1].count++;
      if (check_black())
      {
        square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
        square[x_1][y_1].set_piece_and_color(Knight, Black);
        square[x_1][y_1].count--;
        if (square[x_2][y_2].get_piece() != Empty)
        {
          piece_white.pop_back();
        }
        return false;
      }
      return true;
    }
    return false;

  case Bishop:
    if (col == White)
    {
      if (bishop(x_1, y_1, x_2, y_2, col))
      {
        Square tmp;
        tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
        square[x_2][y_2].set_piece_and_color(Bishop, White);
        square[x_1][y_1].set_piece_and_color(Empty, None);
        square[x_1][y_1].count++;
        if (check_white())
        {
          square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
          square[x_1][y_1].set_piece_and_color(Bishop, White);
          square[x_1][y_1].count--;
          if (square[x_2][y_2].get_piece() != Empty)
          {
            piece_black.pop_back();
          }
          return false;
        }
        return true;
      }
      return false;
    }

    else if (bishop(x_1, y_1, x_2, y_2, col))
    {
      Square tmp;
      tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
      square[x_2][y_2].set_piece_and_color(Bishop, Black);
      square[x_1][y_1].set_piece_and_color(Empty, None);
      square[x_1][y_1].count++;
      if (check_black())
      {
        square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
        square[x_1][y_1].set_piece_and_color(Bishop, Black);
        square[x_1][y_1].count--;
        if (square[x_2][y_2].get_piece() != Empty)
        {
          piece_white.pop_back();
        }
        return false;
      }
      return true;
    }
    return false;

  case Pawn:
    if (col == White)
    {
      if (pawn(x_1, y_1, x_2, y_2, col))
      {
        Square tmp;
        tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
        square[x_2][y_2].set_piece_and_color(Pawn, White);
        square[x_1][y_1].set_piece_and_color(Empty, None);
        square[x_1][y_1].count++;
        if (check_white())
        {
          square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
          square[x_1][y_1].set_piece_and_color(Pawn, White);
          square[x_1][y_1].count--;
          if (square[x_2][y_2].get_piece() != Empty)
          {
            piece_black.pop_back();
          }
          return false;
        }
        if (x_2 == 7)
        {
          cout << "Select piecee number :"
               << "1 - Queen" << '\n'
               << "2 - Rook" << '\n'
               << "3 - Knight" << '\n'
               << "4 - Bishop" << endl;
          int temp;
          cin >> temp;
          if (temp > 0 && temp < 5)
          {
            switch (temp)
            {
            case 1:
              square[x_2][y_2].set_piece_and_color(Queen, White);
              square[x_1][y_1].set_piece_and_color(Empty, None);
              square[x_1][y_1].count++;
              break;
            case 2:
              square[x_2][y_2].set_piece_and_color(Rook, White);
              square[x_1][y_1].set_piece_and_color(Empty, None);
              square[x_1][y_1].count++;
              break;
            case 3:
              square[x_2][y_2].set_piece_and_color(Knight, White);
              square[x_1][y_1].set_piece_and_color(Empty, None);
              square[x_1][y_1].count++;
              break;
            case 4:
              square[x_2][y_2].set_piece_and_color(Bishop, White);
              square[x_1][y_1].set_piece_and_color(Empty, None);
              square[x_1][y_1].count++;
              break;
            default:
              break;
            }
          }
          return true;
        }

        return true;
      }
      return false;
    }
    else if (pawn(x_1, y_1, x_2, y_2, col))
    {
      Square tmp;
      tmp.set_piece_and_color(square[x_2][y_2].get_piece(), square[x_2][y_2].get_color());
      square[x_2][y_2].set_piece_and_color(Pawn, Black);
      square[x_1][y_1].set_piece_and_color(Empty, None);
      square[x_1][y_1].count++;
      if (check_black())
      {
        square[x_2][y_2].set_piece_and_color(tmp.get_piece(), tmp.get_color());
        square[x_1][y_1].set_piece_and_color(Pawn, Black);
        square[x_1][y_1].count--;
        if (square[x_2][y_2].get_piece() != Empty)
        {
          piece_white.pop_back();
        }
        return false;
      }
      if (x_2 == 0)
      {
        cout << "Select piecee number :" << '\n'
             << "1 - Queen" << '\n'
             << "2 - Rook" << '\n'
             << "3 - Knight" << '\n'
             << "4 - Bishop" << endl;
        int temp;
        cin >> temp;
        if (temp > 0 && temp < 5)
        {
          switch (temp)
          {
          case 1:
            square[x_2][y_2].set_piece_and_color(Queen, Black);
            square[x_1][y_1].set_piece_and_color(Empty, None);
            square[x_1][y_1].count++;
            break;
          case 2:
            square[x_2][y_2].set_piece_and_color(Rook, Black);
            square[x_1][y_1].set_piece_and_color(Empty, None);
            square[x_1][y_1].count++;
            break;
          case 3:
            square[x_2][y_2].set_piece_and_color(Knight, Black);
            square[x_1][y_1].set_piece_and_color(Empty, None);
            square[x_1][y_1].count++;
            break;
          case 4:
            square[x_2][y_2].set_piece_and_color(Bishop, Black);
            square[x_1][y_1].set_piece_and_color(Empty, None);
            square[x_1][y_1].count++;
            break;
          default:
            break;
          }
        }
        return true;
      }

      return true;
    }
    return false;

  default:
    return false;
  }
}

void Board::taken_pieces(piece pic, color col)
{
  switch (pic)
  {
  case Knight:
    if (col == White)
    {
      piece_white.push_back("\u2658");
    }
    else
    {
      piece_black.push_back("\u265E");
    }
    break;
  case Bishop:
    if (col == White)
    {
      piece_white.push_back("\u2657");
    }
    else
    {
      piece_black.push_back("\u265D");
    }
    break;
  case Rook:
    if (col == White)
    {
      piece_white.push_back("\u2656");
    }
    else
    {
      piece_black.push_back("\u265C");
    }
    break;
  case Queen:
    if (col == White)
    {
      piece_white.push_back("\u2655");
    }
    else
    {
      piece_black.push_back("\u265B");
    }
    break;
  case Pawn:
    if (col == White)
    {
      piece_white.push_back("\u2659");
    }
    else
    {
      piece_black.push_back("\u265F");
    }
    break;

  default:
    break;
  }
}

bool Board::check_white()
{
  square[white_king_cordinate_1][white_king_cordinate_2].current = 0;
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      if (square[i][j].get_color() == Black)
      {
        switch (square[i][j].get_piece())
        {
        case Queen:
          if (queen(i, j, white_king_cordinate_1, white_king_cordinate_2, Black))
          {
            square[white_king_cordinate_1][white_king_cordinate_2].current++;
            check_queen_cordinate(i, j, white_king_cordinate_1, white_king_cordinate_2);
          }
          break;
        case Rook:
          if (rook(i, j, white_king_cordinate_1, white_king_cordinate_2, Black))
          {
            square[white_king_cordinate_1][white_king_cordinate_2].current++;
            check_rook_cordinate(i, j, white_king_cordinate_1, white_king_cordinate_2);
          }
          break;
        case Bishop:
          if (bishop(i, j, white_king_cordinate_1, white_king_cordinate_2, Black))
          {
            square[white_king_cordinate_1][white_king_cordinate_2].current++;
            check_bishop_cordinate(i, j, white_king_cordinate_1, white_king_cordinate_2);
          }
          break;
        case Knight:
          if (knight(i, j, white_king_cordinate_1, white_king_cordinate_2, Black))
          {
            square[white_king_cordinate_1][white_king_cordinate_2].current++;
            index_check.push_back(make_pair(i, j));
          }
          break;
        case Pawn:
          if (pawn(i, j, white_king_cordinate_1, white_king_cordinate_2, Black))
          {
            square[white_king_cordinate_1][white_king_cordinate_2].current++;
            index_check.push_back(make_pair(i, j));
          }
          break;

        default:
          break;
        }
      }
    }
  }
  if (square[white_king_cordinate_1][white_king_cordinate_2].current == 1)
  {
    return true;
  }
  if (square[white_king_cordinate_1][white_king_cordinate_2].current > 1)
  {
    mate_white = 1;
    return true;
  }
  return false;
}

bool Board::check_black()
{
  square[black_king_cordinate_1][black_king_cordinate_2].current = 0;
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      if (square[i][j].get_color() == White)
      {
        switch (square[i][j].get_piece())
        {
        case Queen:
          if (queen(i, j, black_king_cordinate_1, black_king_cordinate_2, White))
          {
            square[black_king_cordinate_1][black_king_cordinate_2].current++;
            check_queen_cordinate(i, j, black_king_cordinate_1, black_king_cordinate_2);
          }
          break;
        case Rook:
          if (rook(i, j, black_king_cordinate_1, black_king_cordinate_2, White))
          {
            square[black_king_cordinate_1][black_king_cordinate_2].current++;
            check_rook_cordinate(i, j, black_king_cordinate_1, black_king_cordinate_2);
          }
          break;
        case Bishop:
          if (bishop(i, j, black_king_cordinate_1, black_king_cordinate_2, White))
          {
            square[black_king_cordinate_1][black_king_cordinate_2].current++;
            check_bishop_cordinate(i, j, black_king_cordinate_1, black_king_cordinate_2);
          }
          break;
        case Knight:
          if (knight(i, j, black_king_cordinate_1, black_king_cordinate_2, White))
          {
            square[black_king_cordinate_1][black_king_cordinate_2].current++;
            index_check.push_back(make_pair(i, j));
          }
          break;
        case Pawn:
          if (pawn(i, j, black_king_cordinate_1, black_king_cordinate_2, White))
          {
            square[black_king_cordinate_1][black_king_cordinate_2].current++;
            index_check.push_back(make_pair(i, j));
          }
          break;

        default:
          break;
        }
      }
    }
  }
  if (square[black_king_cordinate_1][black_king_cordinate_2].current == 1)
  {
    return true;
  }
  if (square[black_king_cordinate_1][black_king_cordinate_2].current > 1)
  {
    mate_black = 1;
    return true;
  }
  return false;
}

void Board::check_bishop_cordinate(int x, int y, int x_1, int y_1)
{
  for (int i = 1; i < 8; ++i)
  {
    if (((x - x_1 == i) || (x - x_1 == -i)) && ((y - y_1 == i) || (y - y_1 == -i)))
    {
      if ((x < x_1) && (y < y_1))
      {
        int temp = x;
        int temp_1 = x_1;
        while (temp_1 != temp)
        {
          index_check.push_back(make_pair(x, y));
          ++temp;
          ++x;
          ++y;
        }
      }
      if ((x > x_1) && (y > y_1))
      {
        int temp = x;
        int temp_1 = x_1;
        while (temp != temp_1)
        {
          index_check.push_back(make_pair(x, y));
          ++temp_1;
          --x;
          --y;
        }
      }
      if ((x < x_1) && (y > y_1))
      {
        int temp = x;
        int temp_1 = x_1;
        while (temp_1 != temp)
        {
          index_check.push_back(make_pair(x, y));
          ++temp;
          ++x;
          --y;
        }
      }
      if ((x > x_1) && (y < y_1))
      {
        int temp = x;
        int temp_1 = x_1;
        while (temp_1 != temp)
        {
          index_check.push_back(make_pair(x, y));
          ++temp_1;
          --x;
          ++y;
        }
      }
    }
  }
}

void Board::check_rook_cordinate(int x, int y, int x_1, int y_1)
{
  int a = 0;
  int b = x_1;
  for (int i = 0; i < 8; ++i)
  {
    if (square[b][a].get_color() != None)
    {
      break;
    }
    else
    {
      index_check.push_back(make_pair(b, a));
      ++a;
    }
  }
  a = 0;
  b = y_1;
  for (int i = 0; i < 8; ++i)
  {
    if (square[a][b].get_color() != None)
    {
      break;
    }
    else
    {
      index_check.push_back(make_pair(a, b));
      ++a;
    }
  }
}

void Board::check_queen_cordinate(int x, int y, int x_1, int y_1)
{
  if (x == x_1 || y == y_1)
  {
    check_rook_cordinate(x, y, x_1, y_1);
  }
  else
  {
    check_bishop_cordinate(x, y, x_1, y_1);
  }
}

void Board::mate()
{
  if (check_black())
  {
    int tmp = 0;
    for (int k = 0; k < index_check.size(); ++k)
    {
      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 8; ++j)
        {

          if (square[i][j].get_color() == Black)
          {
            if (square[i][j].get_piece() == Queen)
            {
              if (queen(i, j, index_check[k].first, index_check[k].second, Black))
              {
                ++tmp;
              }
            }
            if (square[i][j].get_piece() == Rook)
            {
              if (rook(i, j, index_check[k].first, index_check[k].second, Black))
              {
                ++tmp;
              }
            }
            if (square[i][j].get_piece() == Knight)
            {
              if (knight(i, j, index_check[k].first, index_check[k].second, Black))
              {
                ++tmp;
              }
            }
            if (square[i][j].get_piece() == Bishop)
            {
              if (bishop(i, j, index_check[k].first, index_check[k].second, Black))
              {
                ++tmp;
              }
            }
            if (square[i][j].get_piece() == Pawn)
            {
              if (pawn(i, j, index_check[k].first, index_check[k].second, Black))
              {
                ++tmp;
              }
            }
          }

          else if (legal_move(black_king_cordinate_1, black_king_cordinate_2, i, j, Black, King))
          {
            ++tmp;
          }
        }
      }
    }
    if (tmp == 0)
    {
      mate_black = true;
    }
    return;
  }

  if (check_white())
  {
    int tmp = 0;
    for (int k = 0; k < index_check.size(); ++k)
    {
      for (int i = 0; i < 8; ++i)
      {
        for (int j = 0; j < 8; ++j)
        {

          if (square[i][j].get_color() == White)
          {
            if (square[i][j].get_piece() == Queen)
            {
              if (queen(i, j, index_check[k].first, index_check[k].second, White))
              {
                ++tmp;
              }
            }
            if (square[i][j].get_piece() == Rook)
            {
              if (rook(i, j, index_check[k].first, index_check[k].second, White))
              {
                ++tmp;
              }
            }
            if (square[i][j].get_piece() == Knight)
            {
              if (knight(i, j, index_check[k].first, index_check[k].second, White))
              {
                ++tmp;
              }
            }
            if (square[i][j].get_piece() == Bishop)
            {
              if (bishop(i, j, index_check[k].first, index_check[k].second, White))
              {
                ++tmp;
              }
            }
            if (square[i][j].get_piece() == Pawn)
            {
              if (pawn(i, j, index_check[k].first, index_check[k].second, White))
              {
                ++tmp;
              }
            }
          }
          else
          {
            if (legal_move(white_king_cordinate_1, white_king_cordinate_2, i, j, White, King))
            {
              tmp++;
            }
          }
        }
      }
    }
    if (tmp == 0)
    {
      mate_white = true;
    }
    return;
  }
}

void Board::start()
{
  cout << "Move White" << endl;
  string str;
  string str1;
  string st = "White";
  string check = "0";

  while (mate_black == 0 && mate_white == 0)
  {
    cin >> str;
    cin >> str1;
    int y_1 = str[0] - 97;
    int x_1 = str[1] - 49;
    int y_2 = str1[0] - 97;
    int x_2 = str1[1] - 49;
    if ((x_1 <= 7 && x_1 >= 0) &&
        (y_1 <= 7 && y_1 >= 0) &&
        (x_2 <= 7 && x_2 >= 0) &&
        (y_2 <= 7 && y_2 >= 0))
    {
      piece pic = square[x_1][y_1].get_piece();
      color col = square[x_1][y_1].get_color();
      if (col == Black && st == "White")
      {
        if (legal_move(x_1, y_1, x_2, y_2, col, pic))
        {
          if (check_white())
          {
            mate();
            check = "Check";
          }
          else
          {
            check = "0";
          }
          st = "Black";
        }
      }
      if (col == White && st == "Black")
      {
        if (legal_move(x_1, y_1, x_2, y_2, col, pic))
        {
          if (check_black())
          {
            mate();
            check = "Check";
          }
          else
          {
            check = "0";
          }
          st = "White";
        }
      }

      system("clear");
      print();
      cout << "Move " << st << endl;
      if (check != "0")
      {
        cout << check << endl;
      }

      if (mate_white != 0)
      {
        cout << "Black Win" << endl;
      }
      if (mate_black != 0)
      {
        cout << "White Win" << endl;
      }
    }
    else
    {
      cout << " Wrong index!!! " << endl;
    }
  }
}
