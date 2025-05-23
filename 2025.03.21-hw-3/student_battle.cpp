#include <iostream>
#include <ctime>
#include <string>

struct Student
{
	int name;
	int hp;
	int dmg;
	int luck;

	Student(int name, int hp = 100, int dmg = 5, int luck = 10) :
		name(name), hp(hp), dmg(dmg), luck(luck)
	{
	}
	Student(const Student& student) :
		name(student.name),
		hp(student.hp),
		dmg(student.dmg),
		luck(student.luck)
	{}
	~Student() {}
	bool luckWorks()
	{
		return (rand() % 100 < luck);
	}
	bool isDead()
	{
		return (hp < 1);
	}
	void getDmg(int dmg)
	{
		if (luckWorks())
		{		
			dmg /= 2;
		}
		hp -= dmg;
	}
	int makeDmg()
	{
		if (luckWorks())
		{	
			return dmg * 2;
		}
		else
		{
			return dmg;
		}
	}
	void print()
	{
		std::cout << name << " [" << hp << "] (";
		std::cout << "luck=" << luck << ";";
		std::cout << "damage=" << dmg << ")\n";
	}
};

int genLuck()
{
	int luck = rand() % 100 + 1;
	return luck;
}

int genHp()
{
	return (rand() % 30 + 71);
}

int genDmg()
{
	return (rand() % 35 + 1);
}

Student genSt(int i)
{
	return Student(i, genHp(), genDmg(), genLuck());
}

Student battle(Student st1, Student st2)
{
	int round = 1;
	while (!(st1.isDead() || st2.isDead()))
	{
		std::cout << "\t\tROUND " << ++round << "\n";
		st1.print();
		std::cout << "versus\n";
		st2.print();
		st1.getDmg(st2.makeDmg());
		st2.getDmg(st1.makeDmg());
	}

	if (st1.isDead() && st2.isDead())
	{
		std::cout << "DRAW\n";
		if (st1.luck < st2.luck)
		{
			return st1;
		}
		else
		{
			return st2;
		}
	}
	else
	{
		std::cout << (st1.isDead() ? st2.name : st1.name) << " wins\n";
		if (st1.isDead())
		{
			return st2;
		}
		else
		{
			return st1;
		}
	}
}

Student battleNOPRINT(Student st1, Student st2)
{
	int round = 1;
	while (!(st1.isDead() || st2.isDead()))
	{
		st1.getDmg(st2.makeDmg());
		st2.getDmg(st1.makeDmg());
	}

	if (st1.isDead() && st2.isDead())
	{
		if (st1.luck < st2.luck)
		{
			return st1;
		}
		else
		{
			return st2;
		}
	}
	else
	{
		if (st1.isDead())
		{
			return st2;
		}
		else
		{
			return st1;
		}
	}
}

Student* tour(Student* starr, int fightersNumb)
{
	int RoundNumber = 0;
	int memN = fightersNumb;
	while (memN / 2 != 1)
	{
		++RoundNumber;
		memN = memN / 2;
	}
	Student* Final = &(new Student(0, 0, 0, 0))[2];
	for (int r = 0; r < RoundNumber; ++r)
	{
		Student* newstarr = &(new Student(0, 0, 0, 0))[fightersNumb / 2];
		for (int i = 0; i < fightersNumb; ++i)
		{
			newstarr[i] = battleNOPRINT(starr[i], starr[fightersNumb - 1 - i]);
		}
		fightersNumb /= 2;
		if (r == RoundNumber - 1)
		{
			Final = newstarr;
		}
	}
	return Final;
}

int main()
{
	srand(time(0));
	Student* starr = &(new Student(0, 0, 0, 0))[8];
	for (int i = 0; i < 8; ++i)
	{
		starr[i] = genSt(i);
	}
	Student* Final = &(new Student(0, 0, 0, 0))[2];
	Final = tour(starr, 8);
	Final[2].print();
	Final[1].print();
	battle(Final[1], Final[2]);
	return 0;
}
