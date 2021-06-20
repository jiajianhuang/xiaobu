
/*
使用c++语言
2.2即相同author不相邻
2.3即满足2.2的情况下尽量不超过2个连续的category
第一种想到的方法是利用冒泡排序的思想，使2.2成立，再使2.3成立。
在冒泡的下一个循环中，如果上一个2.3的结果与2.2冲突，则会优先2.2	
第二种想到的方法是构建新链表，插入满足条件的 
*/ 
struct FeedItem{
	int itemId;
	string title;
	string pics[];
	string author;
	string category; 
};

//第一种尝试的方法 
List<FeedItem> reorderFeedItems(List<FeedItem> inputItems){
	list<FeedItem>::iterator it1;
	list<FeedItem>::iterator it2;
	
	list<FeedItem> temp;
	for(it1=inputItems.begin();it1!=inputItems.end();it1++)
		for(it2=it1;it2!=inputItems.end()-2;it2++)
			{
				list<FeedItem>::iterator it3;
				list<FeedItem>::iterator it4;
				if(it2.author==it1.author)
				{
					it3 = it2++;
					//查找不同作者的新闻进行交换 
					while(it3.author==it2.author && it3!=inputItems.end()) it3++;
					//交换节点 
					temp = *it2;
					*it2 = *it3;
					*it3 = temp;
					if(it1.category==it2.category==it3.category)
					{
						it4 = it3++;
						//查找不同标签的新闻进行交换 
						while(it3.category==it4.category && it4!=inputItems.end()) it4++;
						temp = *it3;
						*it3 = *it4;
						*it4 = temp;
					}
				}
			}
	list<FeedItem> mylist;
	int count = 0;
	for(it1=inputItems.begin();it1!=inputItems.end();it1++,count++)
	{
		if(count<10)
			mylist.push_back(*it);
	}
	return mylist;
}

//第二种尝试的方法 
List<FeedItem> reorderFeedItems(List<FeedItem> inputItems){
	list<FeedItem> mylist;
	list<FeedItem>::iterator it1;
	list<FeedItem>::iterator it2;
	
	mylist.push_back(inputItems.front());
	inputItems.remove(inputItems.front());
	it2 = mylist.begin();
	
	int count = 1;
	int alarm = 0;
	while(count<=10 && alarm==0)
	{
		//每次都从头搜起，尽量不更改原顺序 
		it1 = inputItems.begin();
		//搜索不同作者 
		while(it1.author==it2.author) it1++;
		//最坏情况，没有不同作者，则将alarm置为1 
		if(it1==inputItems.end()) alarm = 1;
		if(it1.author!=it2.author){
			mylist.push_back(*it1);
			inputItems.remove(*it2);
			it2++;
		}
	}
  //补足 10个
	if(alarm==1)
	{
		while(count<=10)
		{
			it1 = inputItems.begin();
			mylist.push_back(*it1);
		}
		
	}
	//新列表已满足2.2条件，开始实现2.3条件 
	it2 = mylist.begin();
	list<FeedItem>::iterator it3;
	list<FeedItem>::iterator it4;
	list<FeedItem>::iterator it5;
	it3 = it2++;
	it4 = it3++;
	it5 = it4++;
	//一个思路就是从inputItems里找符合条件的节点来替换连续3个相同标签的第3个标签 
	for(it2;it2!=inputItems.end(),it3!=inputItems.end(),it4!=inputItems.end(),it5!=inputItems.end();it2++,it3++,it4++,it5++)
	{
		if(it2.category==it3.category==it4.category)
		{
			it1 = inputItems.begin();
			while(it1.category==it3.category==it5.category && it1.author==it3.author==it5.author) it1++;
			if(it1!+inputItems.end())
			{
				swap(*it4,*it1);
			}
		}
	}
	//另一个思路就是在原链表里通过类似冒泡交换，尽可能满足2.3条件,即类似第一种方法。 
	
	return mylist; 
}

