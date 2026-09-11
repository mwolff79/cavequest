{$R+}
overlay procedure OvArmory;
var
  I                 : byte;
  TempSelection     : byte;
  Selection         : byte;
  PreviousSelection : byte;
  Done              : boolean;
  C                 : char;
  Proceeds          : real;
  WaitC             : char;
  BaseWeight        : integer;

  procedure NotEnoughSilver;
  begin
    TextColor(4);
    GotoXY(3,14);
    write('Ye have not enough silver, stranger.');
    Delay(1500);
    GotoXY(3,14);
    write('                                     ')
  end;

  procedure SetArmor(T : byte);
  begin
    GotoXY(10,6);
    write('             ');
    GotoXY(10,6);
    Character.ArmorType := T;
    case T of
      1: write('Leather');
      2: write('Ring Mail');
      3: write('Chain Mail');
      4: write('Partial Plate');
      5: write('Full Plate')
    end
  end;

  procedure SetBlade(T : byte);
  begin
    GotoXY(50,6);
    write('             ');
    GotoXY(50,6);
    Character.BladeType := T;
    case T of
      1: write('Knife');
      2: write('Dagger');
      3: write('Short Sword');
      4: write('Broad Sword');
      5: write('Great Sword')
    end
  end;

  procedure SpendSilver(Amount : integer);
  begin
    Character.Silver := Character.Silver - Amount;
    GotoXY(31,4);
    write('          ');
    GotoXY(31,4);
    write(Character.Silver:9:2)
  end;

  procedure RecalculateWeight;
  begin
    Character.Weight := BaseWeight;

    case Character.ArmorType of
      1: Character.Weight := Character.Weight + 5;
      2: Character.Weight := Character.Weight + 10;
      3: Character.Weight := Character.Weight + 15;
      4: Character.Weight := Character.Weight + 25;
      5: Character.Weight := Character.Weight + 40
    end;

    case Character.BladeType of
      1: Character.Weight := Character.Weight + 2;
      2: Character.Weight := Character.Weight + 4;
      3: Character.Weight := Character.Weight + 10;
      4: Character.Weight := Character.Weight + 20;
      5: Character.Weight := Character.Weight + 40
    end;

    Character.Weight := Character.Weight + Character.Arrows;
    Character.Weight := Character.Weight + Character.Spears * 2;

    if Character.BowOwned then
      Character.Weight := Character.Weight + 10;

    case Character.ShieldType of
      1: Character.Weight := Character.Weight + 5;
      2: Character.Weight := Character.Weight + 10
    end;

    GotoXY(58,4);
    write('    ');
    GotoXY(58,4);
    write(Character.Weight)
  end;

begin
  GraphBackground(1);
  TextMode(3);
  GraphColorMode;
  Palette(0);

  { The original removes equipped-item weight before the armory intro. }
  case Character.ArmorType of
    1: Character.Weight := Character.Weight - 5;
    2: Character.Weight := Character.Weight - 10;
    3: Character.Weight := Character.Weight - 15;
    4: Character.Weight := Character.Weight - 25;
    5: Character.Weight := Character.Weight - 40
  end;

  case Character.BladeType of
    1: Character.Weight := Character.Weight - 2;
    2: Character.Weight := Character.Weight - 4;
    3: Character.Weight := Character.Weight - 10;
    4: Character.Weight := Character.Weight - 20;
    5: Character.Weight := Character.Weight - 40
  end;

  case Character.ShieldType of
    1: Character.Weight := Character.Weight - 5;
    2: Character.Weight := Character.Weight - 10
  end;

  Character.Weight := Character.Weight - Character.Arrows;
  Character.Weight := Character.Weight - Character.Spears * 2;

  if Character.BowOwned then
    Character.Weight := Character.Weight - 10;

  writeln;
  writeln('Welcome to the armory, ', Character.Name, '.');
  writeln;
  writeln('Say, you''re new to these parts,');
  writeln('aren''t you?');

  if Character.TreasureCount > 0 then
  begin
    writeln;
    writeln('Ahh, I see you have some treasures');
    writeln('to trade.');
    writeln;
    writeln('I''ll convert these to silver for you.');

    Proceeds := 0;

    for I := 1 to Character.TreasureCount do
    begin
      case Character.Treasures[I] of
         1: Proceeds := Proceeds + 0.1;
         2: Proceeds := Proceeds + 1;
         3: Proceeds := Proceeds + 5;
         4: Proceeds := Proceeds + 10;
         5: Proceeds := Proceeds + 100;
         6: Proceeds := Proceeds + 1;
         7: Proceeds := Proceeds + 10;
         8: Proceeds := Proceeds + 50;
         9: Proceeds := Proceeds + 100;
        10: Proceeds := Proceeds + 1000;
        11: Proceeds := Proceeds + 10;
        12: Proceeds := Proceeds + 100;
        13: Proceeds := Proceeds + 500;
        14: Proceeds := Proceeds + 1000;
        15: Proceeds := Proceeds + 10000;
        16: Proceeds := Proceeds + 100;
        17: Proceeds := Proceeds + 200;
        18: Proceeds := Proceeds + 200;
        19: Proceeds := Proceeds + 250;
        20: Proceeds := Proceeds + 225;
        21: Proceeds := Proceeds + 20
      end;

      Character.Weight := Character.Weight -
                          TreasureWeight(Character.Treasures[I])
    end;

    writeln;
    writeln('Here be ', Proceeds:8:2, ' silvers for you.');

    Character.Silver := Character.Silver + Proceeds;
    Character.TreasureCount := 0
  end;

  BaseWeight := Character.Weight;

  writeln;
  writeln('Press any key when you''re ready.');
  Read(Kbd, WaitC);

  Selection := 1;
  PreviousSelection := 1;
  Done := false;

  TextMode(3);
  TextBackground(0);
  TextColor(2);
  ClrScr;

  { Original Armory CP437 frame.  This is deliberately inline: the 1985
    binary contains this large drawing block in the Armory main body. }

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
  for I := 2 to 22 do write(Chr(196));
  write(Chr(194));
  for I := 24 to 29 do write(Chr(196));
  write(Chr(194));
  for I := 31 to 38 do write(Chr(196));
  write(Chr(194));
  write(Chr(194));
  for I := 41 to 63 do write(Chr(196));
  write(Chr(194));
  for I := 65 to 70 do write(Chr(196));
  write(Chr(194));
  for I := 72 to 79 do write(Chr(196));
  write(Chr(180));

  write(Chr(179));
  GotoXY(23,6); write(Chr(179));
  GotoXY(30,6); write(Chr(179));
  GotoXY(39,6); write(Chr(179));
  write(Chr(179));
  GotoXY(64,6); write(Chr(179));
  GotoXY(71,6); write(Chr(179));
  GotoXY(80,6); write(Chr(179));

  write(Chr(195));
  for I := 2 to 22 do write(Chr(196));
  write(Chr(197));
  for I := 24 to 29 do write(Chr(196));
  write(Chr(197));
  for I := 31 to 38 do write(Chr(196));
  write(Chr(180));
  write(Chr(195));
  for I := 41 to 63 do write(Chr(196));
  write(Chr(197));
  for I := 65 to 70 do write(Chr(196));
  write(Chr(197));
  for I := 72 to 79 do write(Chr(196));
  write(Chr(179));

  for I := 8 to 12 do
  begin
    GotoXY(1,I);  write(Chr(179));
    GotoXY(23,I); write(Chr(179));
    GotoXY(30,I); write(Chr(179));
    GotoXY(39,I); write(Chr(179));
    GotoXY(40,I); write(Chr(179));
    GotoXY(64,I); write(Chr(179));
    GotoXY(71,I); write(Chr(179));
    GotoXY(80,I); write(Chr(179))
  end;

  write(Chr(195));
  for I := 2 to 22 do write(Chr(196));
  write(Chr(193));
  for I := 24 to 29 do write(Chr(196));
  write(Chr(193));
  for I := 31 to 38 do write(Chr(196));
  write(Chr(193));
  write(Chr(193));
  for I := 41 to 63 do write(Chr(196));
  write(Chr(193));
  for I := 65 to 70 do write(Chr(196));
  write(Chr(193));
  for I := 72 to 79 do write(Chr(196));
  write(Chr(180));

  write(Chr(179));
  GotoXY(80,14); write(Chr(179));

  write(Chr(195));
  for I := 2 to 10 do write(Chr(196));
  write(Chr(194));
  for I := 12 to 20 do write(Chr(196));
  write(Chr(194));
  for I := 22 to 27 do write(Chr(196));
  write(Chr(194));
  for I := 29 to 36 do write(Chr(196));
  write(Chr(194));
  write(Chr(196));
  write(Chr(196));
  write(Chr(194));
  for I := 41 to 55 do write(Chr(196));
  write(Chr(194));
  for I := 57 to 62 do write(Chr(196));
  write(Chr(194));
  for I := 64 to 79 do write(Chr(196));
  write(Chr(180));

  write(Chr(179));
  GotoXY(11,16); write(Chr(179));
  GotoXY(21,16); write(Chr(179));
  GotoXY(28,16); write(Chr(179));
  GotoXY(37,16); write(Chr(179));
  GotoXY(40,16); write(Chr(179));
  GotoXY(56,16); write(Chr(179));
  GotoXY(63,16); write(Chr(179));
  GotoXY(80,16); write(Chr(179));

  write(Chr(179));
  GotoXY(11,17); write(Chr(179));
  GotoXY(21,17); write(Chr(179));
  GotoXY(28,17); write(Chr(179));
  GotoXY(37,17); write(Chr(179));
  GotoXY(40,17); write(Chr(179));
  GotoXY(56,17); write(Chr(179));
  GotoXY(63,17); write(Chr(179));
  GotoXY(80,17); write(Chr(179));

  write(Chr(195));
  for I := 2 to 10 do write(Chr(196));
  write(Chr(197));
  for I := 12 to 20 do write(Chr(196));
  write(Chr(197));
  for I := 22 to 27 do write(Chr(196));
  write(Chr(197));
  for I := 29 to 36 do write(Chr(196));
  write(Chr(180));
  write(Chr(32));
  write(Chr(32));
  write(Chr(195));
  for I := 41 to 55 do write(Chr(196));
  write(Chr(197));
  for I := 57 to 62 do write(Chr(196));
  write(Chr(197));
  for I := 64 to 79 do write(Chr(196));
  write(Chr(180));

  for I := 19 to 21 do
  begin
    GotoXY(1,I);  write(Chr(179));
    GotoXY(11,I); write(Chr(179));
    GotoXY(21,I); write(Chr(179));
    GotoXY(28,I); write(Chr(179));
    GotoXY(37,I); write(Chr(179));
    GotoXY(40,I); write(Chr(179));
    GotoXY(56,I); write(Chr(179));
    GotoXY(63,I); write(Chr(179));
    GotoXY(80,I); write(Chr(179))
  end;

  write(Chr(195));
  for I := 2 to 10 do write(Chr(196));
  write(Chr(193));
  for I := 12 to 20 do write(Chr(196));
  write(Chr(193));
  for I := 22 to 27 do write(Chr(196));
  write(Chr(193));
  for I := 29 to 36 do write(Chr(196));
  write(Chr(193));
  write(Chr(196));
  write(Chr(196));
  write(Chr(193));
  for I := 41 to 55 do write(Chr(196));
  write(Chr(193));
  for I := 57 to 62 do write(Chr(196));
  write(Chr(193));
  for I := 64 to 79 do write(Chr(196));
  write(Chr(180));

  write(Chr(179));
  GotoXY(80,23); write(Chr(179));

  write(Chr(179));
  GotoXY(80,24); write(Chr(179));

  write(Chr(192));
  for I := 2 to 79 do write(Chr(196));

  TextColor(4);
  GotoXY(35,2); write('THE ARMORY');

  TextColor(15);
  GotoXY(13,4); write('Silver available:');
  GotoXY(42,4); write('Weight carried:');

  GotoXY(3,6);  write('Armor:');
  GotoXY(25,6); write('Cost');
  GotoXY(32,6); write('Weight');
  GotoXY(42,6); write('Weapon:');
  GotoXY(66,6); write('Cost');
  GotoXY(73,6); write('Weight');

  { Armor names. }
  GotoXY(3,8);  write('Leather');
  GotoXY(3,9);  write('Ring Mail');
  GotoXY(3,10); write('Chain Mail');
  GotoXY(3,11); write('Partial Plate');
  GotoXY(3,12); write('Full Plate');

  { Armor costs.  The original uses literal output, not integer formatting. }
  GotoXY(26,8);  write('250');
  GotoXY(26,9);  write('500');
  GotoXY(26,10); write('750');
  GotoXY(25,11); write('1250');
  GotoXY(25,12); write('2000');

  { Armor weights. }
  GotoXY(35,8);  write('5');
  GotoXY(34,9);  write('10');
  GotoXY(34,10); write('15');
  GotoXY(34,11); write('25');
  GotoXY(34,12); write('40');

  { Weapon names. }
  GotoXY(42,8);  write('Knife');
  GotoXY(42,9);  write('Dagger');
  GotoXY(42,10); write('Short Sword');
  GotoXY(42,11); write('Broad Sword');
  GotoXY(42,12); write('Great Sword');

  { Weapon costs. }
  GotoXY(69,8);  write('5');
  GotoXY(68,9);  write('20');
  GotoXY(68,10); write('70');
  GotoXY(67,11); write('130');
  GotoXY(67,12); write('250');

  { Weapon weights. }
  GotoXY(76,8);  write('2');
  GotoXY(76,9);  write('4');
  GotoXY(75,10); write('10');
  GotoXY(75,11); write('20');
  GotoXY(75,12); write('40');

  GotoXY(3,16);  write('Item');
  GotoXY(13,16); write('Current');
  GotoXY(13,17); write('number');
  GotoXY(23,16); write('Cost');
  GotoXY(30,16); write('Weight');
  GotoXY(31,17); write('each');

  GotoXY(42,16); write('Shield:');
  GotoXY(58,16); write('Cost');
  GotoXY(69,16); write('Weight');

  { Consumable/equipment names. }
  GotoXY(3,19); write('Arrows');
  GotoXY(3,20); write('Spears');
  GotoXY(3,21); write('Bow');

  { Costs. }
  GotoXY(25,19); write('2');
  GotoXY(25,20); write('5');
  GotoXY(24,21); write('50');

  { Weights. }
  GotoXY(33,19); write('1');
  GotoXY(33,20); write('2');
  GotoXY(32,21); write('10');

  { Shield names, costs and weights. }
  GotoXY(42,19); write('Small shield');
  GotoXY(42,20); write('Large shield');
  GotoXY(42,21); write('Leave here');

  GotoXY(59,19); write('250');
  GotoXY(59,20); write('500');
  GotoXY(72,19); write('5');
  GotoXY(71,20); write('10');

  TextColor(14);
  GotoXY(3,23);
  write('Press enter to "buy" an indicated item or to leave.');
  GotoXY(3,24);
  write('Use cursor control keys to select item.');

  { The original fills the live values only after the static table/instructions. }
  TextColor(5);

  GotoXY(31,4);
  write(Character.Silver:9:2);

  RecalculateWeight;

  GotoXY(10,6);
  case Character.ArmorType of
    0: write('None');
    1: write('Leather');
    2: write('Ring Mail');
    3: write('Chain Mail');
    4: write('Partial Plate');
    5: write('Full Plate')
  end;

  GotoXY(50,6);
  case Character.BladeType of
    0: write('None');
    1: write('Knife');
    2: write('Dagger');
    3: write('Short Sword');
    4: write('Broad Sword');
    5: write('Great Sword')
  end;

  GotoXY(15,19); write(Character.Arrows);
  GotoXY(15,20); write(Character.Spears);

  if not Character.BowOwned then
  begin
    GotoXY(15,21); write('No')
  end
  else
  begin
    GotoXY(15,21); write('Yes')
  end;

  GotoXY(42,17);
  case Character.ShieldType of
    0: write('None');
    1: write('Small Shield');
    2: write('Large Shield')
  end;

  repeat
    { Original redraws the old selection in white and the current
      selection in red using one two-iteration loop. }
    for I := 1 to 2 do
    begin
      if I = 1 then
      begin
        TextColor(15);
        TempSelection := PreviousSelection
      end
      else
      begin
        TextColor(4);
        TempSelection := Selection
      end;

      case TempSelection of
         1: begin GotoXY(3,8);  write('Leather') end;
         2: begin GotoXY(3,9);  write('Ring Mail') end;
         3: begin GotoXY(3,10); write('Chain Mail') end;
         4: begin GotoXY(3,11); write('Partial Plate') end;
         5: begin GotoXY(3,12); write('Full Plate') end;
         6: begin GotoXY(3,19); write('Arrow') end;
         7: begin GotoXY(3,20); write('Spears') end;
         8: begin GotoXY(3,21); write('Bow') end;
         9: begin GotoXY(42,8);  write('Knife') end;
        10: begin GotoXY(42,9);  write('Dagger') end;
        11: begin GotoXY(42,10); write('Short Sword') end;
        12: begin GotoXY(42,11); write('Broad Sword') end;
        13: begin GotoXY(42,12); write('Great Sword') end;
        14: begin GotoXY(42,19); write('Small Shield') end;
        15: begin GotoXY(42,20); write('Large Shield') end;
        16: begin GotoXY(42,21); write('Leave here') end
      end;

      if I = 1 then
        write('  ')
      else
        write(' <')
    end;

    Read(Kbd, C);
    if (C = #27) and KeyPressed then
      Read(Kbd, C);

    TextColor(5);

    case C of
      #13:
        case Selection of
          1:
            if Character.Silver >= 250 then
            begin
              SetArmor(1);
              SpendSilver(250);
              RecalculateWeight
            end
            else NotEnoughSilver;

          2:
            if Character.Silver >= 500 then
            begin
              SetArmor(2);
              SpendSilver(500);
              RecalculateWeight
            end
            else NotEnoughSilver;

          3:
            if Character.Silver >= 750 then
            begin
              SetArmor(3);
              SpendSilver(750);
              RecalculateWeight
            end
            else NotEnoughSilver;

          4:
            if Character.Silver >= 1250 then
            begin
              SetArmor(4);
              SpendSilver(1250);
              RecalculateWeight
            end
            else NotEnoughSilver;

          5:
            if Character.Silver >= 2000 then
            begin
              SetArmor(5);
              SpendSilver(2000);
              RecalculateWeight
            end
            else NotEnoughSilver;

          6:
            if Character.Silver >= 2 then
            begin
              Character.Arrows := Character.Arrows + 1;
              GotoXY(15,19); write(Character.Arrows);
              SpendSilver(2);
              RecalculateWeight
            end
            else NotEnoughSilver;

          7:
            if Character.Silver >= 5 then
            begin
              Character.Spears := Character.Spears + 1;
              GotoXY(15,20); write(Character.Spears);
              SpendSilver(5);
              RecalculateWeight
            end
            else NotEnoughSilver;

          8:
            if Character.Silver >= 50 then
            begin
              Character.BowOwned := true;
              GotoXY(15,21); write('Yes');
              SpendSilver(50);
              RecalculateWeight
            end
            else NotEnoughSilver;

          9:
            if Character.Silver >= 5 then
            begin
              SetBlade(1);
              SpendSilver(5);
              RecalculateWeight
            end
            else NotEnoughSilver;

          10:
            if Character.Silver >= 20 then
            begin
              SetBlade(2);
              SpendSilver(20);
              RecalculateWeight
            end
            else NotEnoughSilver;

          11:
            if Character.Silver >= 70 then
            begin
              SetBlade(3);
              SpendSilver(70);
              RecalculateWeight
            end
            else NotEnoughSilver;

          12:
            if Character.Silver >= 130 then
            begin
              SetBlade(4);
              SpendSilver(130);
              RecalculateWeight
            end
            else NotEnoughSilver;

          13:
            if Character.Silver >= 250 then
            begin
              SetBlade(5);
              SpendSilver(250);
              RecalculateWeight
            end
            else NotEnoughSilver;

          14:
            if Character.Silver >= 250 then
            begin
              Character.ShieldType := 1;
              GotoXY(42,17); write('Small Shield');
              SpendSilver(250);
              RecalculateWeight
            end
            else NotEnoughSilver;

          15:
            if Character.Silver >= 500 then
            begin
              Character.ShieldType := 2;
              GotoXY(42,17); write('Large Shield');
              SpendSilver(500);
              RecalculateWeight
            end
            else NotEnoughSilver
        else
          Done := true
        end;

      #75, #77:
        begin
          PreviousSelection := Selection;
          if Selection < 9 then
            Selection := Selection + 8
          else
            Selection := Selection - 8
        end;

      #80:
        begin
          PreviousSelection := Selection;
          if Selection = 16 then
            Selection := 1
          else
            Selection := Selection + 1
        end;

      #72:
        begin
          PreviousSelection := Selection;
          if Selection = 1 then
            Selection := 16
          else
            Selection := Selection - 1
        end
    end
  until Done
end;
{$R-}
{$R-}
