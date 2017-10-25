#ifndef  __FRIENDEX_H__
#define __FRIENDEX_H__
template<class T>
class Defender {
public:
	friend T;
	void Defence(int x, int y){ }
	void Tackle(int x, int y){ }
private:
	int pos_x = 15;
	int pos_y = 0;
	int speed = 2;
	int stamina = 120;
};

template<class T>
class Attacker {
public:
	friend T;
	void Move(int x, int y){ }
	void SpeedUp(float ratio){ }
private:
	int pos_x	= 0;
	int pos_y	= -30;
	int speed	= 3;
	int stamina = 100;
};

class Validator;

using DefenderT = Defender<Validator>;
using AttackerT = Attacker<Validator>;

class Validator {
public:
	void Validate(int x, int y, DefenderT & d){
		d.Defence(x, y);
	}
	void Validate(int x, int y, AttackerT & a){
		a.Move(x, y);
	}
};

void FriendExTest() {
	DefenderT d;
	AttackerT a;
	a.Move(15, 30);
	d.Defence(15, 30);
	a.SpeedUp(1.5f);
	d.Defence(15, 30);
	Validator v;
	v.Validate(7, 0, d);
	v.Validate(1, -10, a);
}

#endif