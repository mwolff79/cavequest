{$R+}
overlay procedure OvZeusEnhancement;
var
  I                 : byte;
  Selection         : byte;
  PreviousSelection : byte;
  Done              : boolean;
  C                 : char;

  procedure UnableToIncrease;
  begin
    TextColor(4);
    GotoXY(39,17);
    write('Unable to increase it.');
    Delay(1500);
    GotoXY(39,17);
    write('                         ')
  end;

begin
  Selection := 1;
  PreviousSelection := 1;
  Done := false;

  TextMode(3);
  TextBackground(0);
  TextColor(2);
  ClrScr;

  { Original $0E07 overlay draws the complete CP437 frame directly. }
  write(Chr(218));
  for I := 2 to 79 do write(Chr(196));
  write(Chr(191));
  write(Chr(179));
  GotoXY(80,2); write(Chr(179));

  write(Chr(195));
  for I := 2 to 79 do write(Chr(196));
  write(Chr(180));
  write(Chr(179));
  GotoXY(80,4); write(Chr(179));

  write(Chr(195));
  for I := 2 to 17 do write(Chr(196));
  write(Chr(194));
  for I := 19 to 25 do write(Chr(196));
  write(Chr(194));
  for I := 27 to 34 do write(Chr(196));
  write(Chr(194));
  for I := 36 to 79 do write(Chr(196));
  write(Chr(180));

  write(Chr(179));
  GotoXY(18,6); write(Chr(179));
  GotoXY(26,6); write(Chr(179));
  GotoXY(35,6); write(Chr(179));
  GotoXY(80,6); write(Chr(179));

  write(Chr(179));
  GotoXY(18,7); write(Chr(179));
  GotoXY(26,7); write(Chr(179));
  GotoXY(35,7); write(Chr(179));
  GotoXY(80,7); write(Chr(179));

  write(Chr(195));
  for I := 2 to 17 do write(Chr(196));
  write(Chr(197));
  for I := 19 to 25 do write(Chr(196));
  write(Chr(197));
  for I := 27 to 34 do write(Chr(196));
  write(Chr(197));
  for I := 36 to 79 do write(Chr(196));
  write(Chr(180));

  for I := 9 to 22 do
  begin
    GotoXY(1,I);  write(Chr(179));
    GotoXY(18,I); write(Chr(179));
    GotoXY(26,I); write(Chr(179));
    GotoXY(35,I); write(Chr(179));
    GotoXY(80,I); write(Chr(179))
  end;

  write(Chr(192));
  for I := 2 to 17 do write(Chr(196));
  write(Chr(193));
  for I := 19 to 25 do write(Chr(196));
  write(Chr(193));
  for I := 27 to 34 do write(Chr(196));
  write(Chr(193));
  for I := 36 to 79 do write(Chr(196));
  write(Chr(217));

  TextColor(4);
  GotoXY(32,2); write('Configure ', Character.Name);

  TextColor(15);
  GotoXY(3,4);  write('Life points available:');
  GotoXY(3,6);  write('Attribute');
  GotoXY(19,6); write('Current');
  GotoXY(29,6); write('Cost');
  GotoXY(38,6); write('Information');
  GotoXY(20,7); write('value');

  GotoXY(3,10); write('Intelligence');
  GotoXY(3,12); write('Charisma');
  GotoXY(3,14); write('Strength');
  GotoXY(3,16); write('Dexterity');
  GotoXY(3,18); write('Stamina');
  GotoXY(3,20); write('Wizard skills');
  GotoXY(3,22); write('Leave here');

  GotoXY(29,10); write('200');
  GotoXY(29,12); write('200');
  GotoXY(29,14); write('300');
  GotoXY(29,16); write('200');
  GotoXY(29,18); write('300');
  GotoXY(29,20); write('300');

  TextColor(14);
  GotoXY(37,10); write('Press enter to "buy" a step up in value.');
  GotoXY(37,12); write('Use cursor control keys to select item.');
  GotoXY(37,14); write('Extra life points will be converted to');
  GotoXY(39,15); write('Silver.');

  TextColor(5);
  GotoXY(26,4); write(Character.LifePoints:6:0);
  GotoXY(21,10); write(Character.Intelligence);
  GotoXY(21,12); write(Character.Charisma);
  GotoXY(21,14); write(Character.Strength);
  GotoXY(21,16); write(Character.Dexterity);
  GotoXY(21,18); write(Character.Stamina);
  GotoXY(21,20); write(Character.WizardSkills);

  repeat
    TextColor(15);
    case PreviousSelection of
      1: begin GotoXY(3,10); write('Intelligence') end;
      2: begin GotoXY(3,12); write('Charisma') end;
      3: begin GotoXY(3,14); write('Strength') end;
      4: begin GotoXY(3,16); write('Dexterity') end;
      5: begin GotoXY(3,18); write('Stamina') end;
      6: begin GotoXY(3,20); write('Wizard skills') end;
      7: begin GotoXY(3,22); write('Leave here') end
    end;

    TextColor(4);
    case Selection of
      1: begin GotoXY(3,10); write('Intelligence') end;
      2: begin GotoXY(3,12); write('Charisma') end;
      3: begin GotoXY(3,14); write('Strength') end;
      4: begin GotoXY(3,16); write('Dexterity') end;
      5: begin GotoXY(3,18); write('Stamina') end;
      6: begin GotoXY(3,20); write('Wizard skills') end;
      7: begin GotoXY(3,22); write('Leave here') end
    end;

    Read(Kbd, C);
    if (C = #27) and KeyPressed then Read(Kbd, C);

    TextColor(5);
    case C of
      #13:
        begin
          if Selection = 1 then
          begin
            if (Character.Intelligence < 18) and
               (Character.LifePoints >= 200) then
            begin
              Character.Intelligence := Character.Intelligence + 1;
              GotoXY(21,10); write(Character.Intelligence);
              Character.LifePoints := Character.LifePoints - 200;
              GotoXY(26,4); write('       ');
              GotoXY(26,4); write(Character.LifePoints:6:0)
            end
            else
              UnableToIncrease
          end
          else if Selection = 2 then
          begin
            if (Character.Charisma < 18) and
               (Character.LifePoints >= 200) then
            begin
              Character.Charisma := Character.Charisma + 1;
              GotoXY(21,12); write(Character.Charisma);
              Character.LifePoints := Character.LifePoints - 200;
              GotoXY(26,4); write('       ');
              GotoXY(26,4); write(Character.LifePoints:6:0)
            end
            else
              UnableToIncrease
          end
          else if Selection = 3 then
          begin
            if (Character.Strength < 18) and
               (Character.LifePoints >= 300) then
            begin
              Character.Strength := Character.Strength + 1;
              GotoXY(21,14); write(Character.Strength);
              Character.LifePoints := Character.LifePoints - 300;
              GotoXY(26,4); write('       ');
              GotoXY(26,4); write(Character.LifePoints:6:0)
            end
            else
              UnableToIncrease
          end
          else if Selection = 4 then
          begin
            if (Character.Dexterity < 18) and
               (Character.LifePoints >= 200) then
            begin
              Character.Dexterity := Character.Dexterity + 1;
              GotoXY(21,16); write(Character.Dexterity);
              Character.LifePoints := Character.LifePoints - 200;
              GotoXY(26,4); write('       ');
              GotoXY(26,4); write(Character.LifePoints:6:0)
            end
            else
              UnableToIncrease
          end
          else if Selection = 5 then
          begin
            if (Character.Stamina < 18) and
               (Character.LifePoints >= 300) then
            begin
              Character.Stamina := Character.Stamina + 1;
              GotoXY(21,18); write(Character.Stamina);
              Character.LifePoints := Character.LifePoints - 300;
              GotoXY(26,4); write('       ');
              GotoXY(26,4); write(Character.LifePoints:6:0)
            end
            else
              UnableToIncrease
          end
          else if Selection = 6 then
          begin
            if (Character.WizardSkills < 18) and
               (Character.LifePoints >= 300) then
            begin
              Character.WizardSkills := Character.WizardSkills + 1;
              GotoXY(21,20); write(Character.WizardSkills);
              Character.LifePoints := Character.LifePoints - 300;
              GotoXY(26,4); write('       ');
              GotoXY(26,4); write(Character.LifePoints:6:0)
            end
            else
              UnableToIncrease
          end
          else
            Done := true
        end;

      #72:
        begin
          PreviousSelection := Selection;
          Selection := Selection - 1;
          if Selection = 0 then Selection := 7
        end;

      #80:
        begin
          PreviousSelection := Selection;
          Selection := Selection + 1;
          if Selection = 8 then Selection := 1
        end
    end
  until Done;

  Character.Silver := Character.Silver + Character.LifePoints;
  Character.LifePoints := 0
end;
{$R-}

overlay procedure OvZeusTransport;
var
  I     : integer;
  Dummy : byte;
begin
  { Recovered original $2107 sequence.  These are TP3 GRAPH.BIN calls,
    not BIOS wrapper procedures. }
  GraphColorMode;
  Palette(3);
  GraphBackground(0);

  for I := 1 to 200 do
    Plot(Random(320), Random(200), 3);

  for I := 2000 downto 500 do
  begin
    if SoundOn then Sound(I);
    Delay(5)
  end;

  if SoundOn then Sound(490);
  GraphBackground(9);
  Delay(100);

  if SoundOn then Sound(480);
  GraphBackground(1);
  Delay(100);

  if SoundOn then Sound(470);
  GraphBackground(12);
  Delay(100);

  if SoundOn then Sound(2000);
  GraphBackground(4);
  Delay(100);

  for I := 1 to 20 do
  begin
    if SoundOn then Sound(1500);
    Delay(100);

    if SoundOn then Sound(800);
    Delay(100)
  end;

  NoSound
end;
