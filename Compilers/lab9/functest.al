int func(int param1, boolean param2, int param3)
begin
	return 2;
end
int main(void)
begin
	int array[10];
	int a;
	write "should be 0 and 0";
	array[0] = 0;
	array[2] = 0;
	write array[0];
	write array[2];
	a = 75;
	write "should be 75";
	write a;
	a = func(2, true, a);
	write "should be 2";
	write a;
	array[func(2, true, a)] = func(2, true, a) + 3;
	write "should be 0";
	write array[0];
	write "should be 5";
	write array[2];

end
