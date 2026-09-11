overlay procedure OvTitleAndSound;
var
  C : char;
begin
  TextMode(3);
  TextColor(2);
  TextBackground(0);
  ClrScr;

  writeln('                                    CAVEQUEST');
  writeln;
  writeln('         Copyright 1985 by Lightwave Consultants.  All rights reserved.');
  writeln;
  writeln('                                   version 1.1');
  writeln;
  writeln('    Permission is granted to duplicate and share Cavequest without fee or ');
  writeln('    restriction provided that the duplicate is an honest copy of the ');
  writeln('    distribution diskette. ');
  writeln;
  writeln('    Cavequest is a fantasy role-playing game where the major objective is to ');
  writeln('    lose yourself in another land, in another time.  The designers of ');
  writeln('    Cavequest made every effort to let you be lost in fantasy.  ');
  writeln;
  writeln('    See the SCROLL.OLD file for descriptions, SCROLL.USE file for instructions,');
  writeln('    and SCROLL.HNT file for helping aids in your journey.');
  writeln;
  writeln('         If you would like the next version of Cavequest, Lightwave ');
  writeln('         Consultants asks that you send $35 to Lightwave Consultants; ');
  writeln('         P.O. Box 290539; Tampa, FL  33617.  Subsequent versions of ');
  writeln('         Cavequest promise to be much more involved and different than ');
  writeln('         previous versions.  You will also receive, printed on stylish ');
  writeln('         parchment, the detail of the cave for your current version. ');
  writeln;

  write('Do you wish sound effects? (Y/N)');
  Read(Kbd, C);

  while (C <> 'Y') and (C <> 'y') and
        (C <> 'N') and (C <> 'n') do
  begin
    writeln;
    write('Please press either "Y" or "N"');
    Read(Kbd, C)
  end;

  {$R+}
  if (C = 'Y') or (C = 'y') then
    SoundOn := true
  else
    SoundOn := false;
  {$R-}
end;
