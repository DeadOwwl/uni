#pragma once
#include <iostream>

class Tree
{
private:
	struct TreeItem {
		int Info;
		TreeItem* RSon;
		TreeItem* LSon;
		TreeItem* Father;
		TreeItem() { LSon = RSon = Father = NULL; }
	};
	TreeItem* Root;
public:
	Tree() { Root = NULL; }
	Tree(const Tree&);
	bool RootCheck()
	{
		if (Root != NULL)
			return true;
		else
			return false;
	}
	const Tree& operator = (const Tree&);
	bool Find(int, TreeItem*&);
	bool FindByValue(int, int&);
	bool Add(int);
	bool Remove(int);
	void Walk(TreeItem* Root, void Func(int&)) const;
	void Walk(void Func(int&)) const;
	void EraseTree(TreeItem*&);
	void Erase();
	virtual ~Tree();
protected:
	TreeItem* Clone(TreeItem*);
	void DeleteTree(TreeItem*);
};

