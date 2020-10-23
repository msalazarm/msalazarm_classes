-- Name: marco salazar, Date: 9/8/2020,
-- purpose: to check if Ada has short circuit evaluation
with Ada.Text_IO; use Ada.Text_IO;

procedure Hello is
   -- function that prints out a line when executed.
   function Short_Circuit(Var : Integer) return Boolean is
   begin
      Put_Line("Function call is executed.");
      return True;
   end Short_Circuit;
begin
   Put_Line("If this line is followed by two lines then Ada does not have short circuit evaluation.");
   -- if ada has short circuit evaluation after it evaluates 1=0 it should not call Short_Circuit()
   if 1=0 and Short_Circuit(1) then
      Put("");
   end if;
   if Short_Circuit(1) and 1=0 then
      Put("");
   end if;
end Hello;
