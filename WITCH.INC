{$R+}
overlay procedure OvWitchesLair;
var
  I                 : byte;
  TempSelection     : byte;
  Selection         : byte;
  PreviousSelection : byte;
  Done              : boolean;
  C                 : char;
  WaitC             : char;
  ArmorTreatmentPrice : integer;
  BladeTreatmentPrice : integer;

  procedure WitchMagicSound;
  var
    I : byte;
  begin
    if SoundOn then
      for I := 1 to 4 do
      begin
        Sound(800); Delay(200);
        Sound(900); Delay(200);
        Sound(800); Delay(200);
        Sound(700); Delay(200)
      end;
    NoSound
  end;

  procedure NotEnoughSilver;
  begin
    TextColor(4);
    GotoXY(3,22);
    write('Ye have not enough silver, stranger.');
    Delay(1500);
    GotoXY(3,22);
    write('                                     ')
  end;

  procedure SpendSilver(Amount : integer);
  begin
    Character.Silver := Character.Silver - Amount;
    GotoXY(27,4);
    write('          ');
    GotoXY(27,4);
    write(Character.Silver:9:2)
  end;

  procedure AddWeight(Amount : byte);
  begin
    GotoXY(25,6);
    write('    ');
    Character.Weight := Character.Weight + Amount;
    GotoXY(25,6);
    write(Character.Weight)
  end;

begin
  ClrScr;
  TextColor(2);
  TextBackground(0);

  writeln;
  writeln('Welcome to the Witches Lair.');
  writeln;
  writeln('Press any key when your''re ready.');
  Read(Kbd, WaitC);

  Selection := 1;
  PreviousSelection := 1;
  Done := false;

  ClrScr;

  { Exact CP437 frame recovered from the final QUEST.000 overlay. }
  write(Chr(218));
  for I := 2 to 79 do write(Chr(196));
  write(Chr(191));

  write(Chr(179));
  GotoXY(80,2); write(Chr(179));

  write(Chr(195));
  for I := 2 to 39 do write(Chr(196));
  write(Chr(194));
  for I := 41 to 63 do write(Chr(196));
  write(Chr(194));
  for I := 65 to 70 do write(Chr(196));
  write(Chr(194));
  for I := 72 to 79 do write(Chr(196));
  write(Chr(180));

  write(Chr(179));
  GotoXY(40,4); write(Chr(179));
  GotoXY(64,4); write(Chr(179));
  GotoXY(71,4); write(Chr(179));
  GotoXY(80,4); write(Chr(179));

  write(Chr(195));
  for I := 2 to 39 do write(Chr(196));
  write(Chr(197));
  for I := 41 to 63 do write(Chr(196));
  write(Chr(197));
  for I := 65 to 70 do write(Chr(196));
  write(Chr(197));
  for I := 72 to 79 do write(Chr(196));
  write(Chr(180));

  for I := 6 to 24 do
  begin
    GotoXY(40,I); write(Chr(179));
    GotoXY(64,I); write(Chr(179));
    GotoXY(71,I); write(Chr(179));
    GotoXY(80,I); write(Chr(179))
  end;

  GotoXY(1,6); write(Chr(179));

  GotoXY(1,7); write(Chr(195));
  for I := 2 to 32 do write(Chr(196));
  write(Chr(194));
  for I := 34 to 39 do write(Chr(196));
  write(Chr(180));

  GotoXY(1,8); write(Chr(179));
  GotoXY(33,8); write(Chr(179));

  GotoXY(1,9); write(Chr(195));
  for I := 2 to 32 do write(Chr(196));
  write(Chr(197));
  for I := 34 to 39 do write(Chr(196));
  write(Chr(180));

  GotoXY(1,10); write(Chr(179));
  GotoXY(33,10); write(Chr(179));

  GotoXY(1,11); write(Chr(179));
  GotoXY(33,11); write(Chr(179));

  GotoXY(1,12); write(Chr(195));
  for I := 2 to 32 do write(Chr(196));
  write(Chr(193));
  for I := 34 to 39 do write(Chr(196));
  write(Chr(180));

  GotoXY(1,13); write(Chr(195));
  for I := 2 to 13 do write(Chr(196));
  write(Chr(194));
  for I := 15 to 23 do write(Chr(196));
  write(Chr(194));
  for I := 25 to 30 do write(Chr(196));
  write(Chr(194));
  for I := 32 to 39 do write(Chr(196));
  write(Chr(180));

  for I := 14 to 15 do
  begin
    GotoXY(1,I);  write(Chr(179));
    GotoXY(14,I); write(Chr(179));
    GotoXY(24,I); write(Chr(179));
    GotoXY(31,I); write(Chr(179))
  end;

  GotoXY(1,16); write(Chr(195));
  for I := 2 to 13 do write(Chr(196));
  write(Chr(197));
  for I := 15 to 23 do write(Chr(196));
  write(Chr(197));
  for I := 25 to 30 do write(Chr(196));
  write(Chr(197));
  for I := 32 to 39 do write(Chr(196));
  write(Chr(180));

  for I := 17 to 18 do
  begin
    GotoXY(1,I);  write(Chr(179));
    GotoXY(14,I); write(Chr(179));
    GotoXY(24,I); write(Chr(179));
    GotoXY(31,I); write(Chr(179))
  end;

  GotoXY(1,19); write(Chr(195));
  for I := 2 to 13 do write(Chr(196));
  write(Chr(193));
  for I := 15 to 23 do write(Chr(196));
  write(Chr(193));
  for I := 25 to 30 do write(Chr(196));
  write(Chr(193));
  for I := 32 to 39 do write(Chr(196));
  write(Chr(180));

  GotoXY(1,20); write(Chr(179));

  GotoXY(1,21); write(Chr(195));
  for I := 2 to 39 do write(Chr(196));
  write(Chr(180));

  for I := 22 to 24 do
  begin
    GotoXY(1,I); write(Chr(179))
  end;

  GotoXY(1,25); write(Chr(192));
  for I := 2 to 39 do write(Chr(196));
  write(Chr(193));
  for I := 41 to 63 do write(Chr(196));
  write(Chr(193));
  for I := 65 to 70 do write(Chr(196));
  write(Chr(193));
  for I := 72 to 79 do write(Chr(196));

  { Static table. }
  TextColor(4);
  GotoXY(32,2); write('THE WITCHES LAIR');

  TextColor(15);
  GotoXY(8,4);  write('Silver available:');
  GotoXY(8,6);  write('Weight carried:');

  GotoXY(3,8);  write('Magic');
  GotoXY(35,8); write('Cost');

  GotoXY(43,4); write('Item');
  GotoXY(66,4); write('Cost');
  GotoXY(73,4); write('Weight');

  GotoXY(3,10); write('Add magic to your armor');
  GotoXY(3,11); write('Add magic to your blade');

  GotoXY(3,14);  write('Weapon');
  GotoXY(16,14); write('Current');
  GotoXY(16,15); write('Number');
  GotoXY(26,14); write('Cost');
  GotoXY(33,14); write('Weight');
  GotoXY(34,15); write('each');

  GotoXY(2,17); write('Magic Arrows');
  GotoXY(27,17); write('10');
  GotoXY(36,17); write('1');

  GotoXY(2,18); write('Magic Spears');
  GotoXY(27,18); write('25');
  GotoXY(36,18); write('2');

  GotoXY(42,6);  write('Magic Cloak');
  GotoXY(42,7);  write('Talisman');
  GotoXY(42,8);  write('Light Burst');
  GotoXY(42,9);  write('Fire Ball');
  GotoXY(42,10); write('Sphere of Essence');
  GotoXY(42,11); write('Pendant of Kort');
  GotoXY(42,12); write('Ring of Zeus');
  GotoXY(42,13); write('Cap of Merlin');
  GotoXY(42,14); write('Spell of Eliakim');
  GotoXY(42,15); write('Spell of Gigos');
  GotoXY(42,16); write('Magic Salt');
  GotoXY(42,20); write('Healing Potion');

  GotoXY(67,6);  write('500');
  GotoXY(66,7);  write('1000');
  GotoXY(69,8);  write('5');
  GotoXY(67,9);  write('160');
  GotoXY(67,10); write('300');
  GotoXY(66,11); write('3000');
  GotoXY(67,12); write('500');
  GotoXY(66,13); write('1000');
  GotoXY(67,14); write('350');
  GotoXY(67,15); write('130');
  GotoXY(67,16); write('520');
  GotoXY(68,20); write('10');

  GotoXY(75,6);  write('8');
  GotoXY(75,7);  write('2');
  GotoXY(75,8);  write('2');
  GotoXY(74,9);  write('10');
  GotoXY(74,10); write('10');
  GotoXY(75,11); write('2');
  GotoXY(75,12); write('3');
  GotoXY(75,13); write('5');
  GotoXY(75,14); write('2');
  GotoXY(75,15); write('2');
  GotoXY(75,16); write('5');
  GotoXY(75,20); write('2');

  GotoXY(3,20); write('Leave here');

  { Treatment costs are locals in the original. }
  case Character.ArmorType of
    0: ArmorTreatmentPrice := 0;
    1: ArmorTreatmentPrice := 125;
    2: ArmorTreatmentPrice := 250;
    3: ArmorTreatmentPrice := 375;
    4: ArmorTreatmentPrice := 625;
    5: ArmorTreatmentPrice := 1000
  end;
  GotoXY(35,10); write(ArmorTreatmentPrice);

  case Character.BladeType of
    0: BladeTreatmentPrice := 0;
    1: BladeTreatmentPrice := 2;
    2: BladeTreatmentPrice := 10;
    3: BladeTreatmentPrice := 35;
    4: BladeTreatmentPrice := 65;
    5: BladeTreatmentPrice := 125
  end;
  GotoXY(35,11); write(BladeTreatmentPrice);

  TextColor(14);
  GotoXY(3,23);
  write('Press enter to "buy" or to leave.');
  GotoXY(3,24);
  write('Use cursor control keys to select.');

  TextColor(5);
  GotoXY(27,4); write(Character.Silver:9:2);
  AddWeight(0);
  GotoXY(18,17); write(Character.MagicArrows);
  GotoXY(18,18); write(Character.MagicSpears);

  repeat
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
         1: begin GotoXY(3,10);  write('Add magic to your armor') end;
         2: begin GotoXY(3,11);  write('Add magic to your blade') end;
         3: begin GotoXY(2,17);  write('Magic Arrows') end;
         4: begin GotoXY(2,18);  write('Magic Spears') end;
         5: begin GotoXY(3,20);  write('Leave here') end;
         6: begin GotoXY(42,6);  write('Magic Cloak') end;
         7: begin GotoXY(42,7);  write('Talisman') end;
         8: begin GotoXY(42,8);  write('Light Burst') end;
         9: begin GotoXY(42,9);  write('Fire Ball') end;
        10: begin GotoXY(42,10); write('Sphere of Essence') end;
        11: begin GotoXY(42,11); write('Pendant of Kort') end;
        12: begin GotoXY(42,12); write('Ring of Zeus') end;
        13: begin GotoXY(42,13); write('Cap of Merlin') end;
        14: begin GotoXY(42,14); write('Spell of Eliakim') end;
        15: begin GotoXY(42,15); write('Spell of Gigos') end;
        16: begin GotoXY(42,16); write('Magic Salt') end;
        17: begin GotoXY(42,20); write('Healing Potion') end
      end
    end;

    Read(Kbd, C);
    if (C = #27) and KeyPressed then
      Read(Kbd, C);

    TextColor(5);

    case C of
      #13:
        case Selection of
          1:
            if (Character.Silver >= ArmorTreatmentPrice) and
               (ArmorTreatmentPrice <> MagicTreatmentDone) then
            begin
              SpendSilver(ArmorTreatmentPrice);
              ArmorTreatmentPrice := MagicTreatmentDone;
              WitchMagicSound
            end
            else
              NotEnoughSilver;

          2:
            if (Character.Silver >= BladeTreatmentPrice) and
               (BladeTreatmentPrice <> MagicTreatmentDone) then
            begin
              SpendSilver(BladeTreatmentPrice);
              BladeTreatmentPrice := MagicTreatmentDone;
              WitchMagicSound
            end
            else
              NotEnoughSilver;

          3:
            if Character.Silver >= 10 then
            begin
              Character.MagicArrows := Character.MagicArrows + 1;
              GotoXY(18,17); write(Character.MagicArrows);
              SpendSilver(10);
              AddWeight(1)
            end
            else
              NotEnoughSilver;

          4:
            if Character.Silver >= 25 then
            begin
              Character.MagicSpears := Character.MagicSpears + 1;
              GotoXY(18,18); write(Character.MagicSpears);
              SpendSilver(25);
              AddWeight(2)
            end
            else
              NotEnoughSilver;

          5:
            Done := true;

          6:
            if Character.Silver >= 500 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicCloak;
              SpendSilver(500);
              AddWeight(8)
            end
            else
              NotEnoughSilver;

          7:
            if Character.Silver >= 1000 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicTalisman;
              SpendSilver(1000);
              AddWeight(2)
            end
            else
              NotEnoughSilver;

          8:
            if Character.Silver >= 5 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicLightBurst;
              SpendSilver(5);
              AddWeight(2)
            end
            else
              NotEnoughSilver;

          9:
            if Character.Silver >= 160 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicFireBall;
              SpendSilver(160);
              AddWeight(10)
            end
            else
              NotEnoughSilver;

          10:
            if Character.Silver >= 300 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicEssence;
              SpendSilver(300);
              AddWeight(10)
            end
            else
              NotEnoughSilver;

          11:
            if Character.Silver >= 3000 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicKort;
              SpendSilver(3000);
              AddWeight(2)
            end
            else
              NotEnoughSilver;

          12:
            if Character.Silver >= 500 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicZeusRing;
              SpendSilver(500);
              AddWeight(3)
            end
            else
              NotEnoughSilver;

          13:
            if Character.Silver >= 1000 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicMerlinCap;
              SpendSilver(1000);
              AddWeight(5)
            end
            else
              NotEnoughSilver;

          14:
            if Character.Silver >= 350 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicEliakim;
              SpendSilver(350);
              AddWeight(2)
            end
            else
              NotEnoughSilver;

          15:
            if Character.Silver >= 130 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicGigos;
              SpendSilver(130);
              AddWeight(2)
            end
            else
              NotEnoughSilver;

          16:
            if Character.Silver >= 520 then
            begin
              Character.MagicCount := Character.MagicCount + 1;
              Character.MagicItems[Character.MagicCount] := MagicSalt;
              SpendSilver(520);
              AddWeight(5)
            end
            else
              NotEnoughSilver;

          17:
            if Character.Silver >= 10 then
            begin
              Character.Potions := Character.Potions + 1;
              SpendSilver(10);
              AddWeight(2)
            end
            else
              NotEnoughSilver
        end;

      #80:
        begin
          PreviousSelection := Selection;
          if Selection = 17 then
            Selection := 1
          else
            Selection := Selection + 1
        end;

      #72:
        begin
          PreviousSelection := Selection;
          if Selection = 1 then
            Selection := 17
          else
            Selection := Selection - 1
        end
    end;

    if Character.MagicCount = 40 then
    begin
      TextColor(4);
      GotoXY(3,22);
      write('                                   ');
      GotoXY(3,22);
      write('Ye have no more pockets!!');
      Delay(3000);
      Done := true
    end
  until Done;

  { Rebuild combat values exactly where the original Witches overlay does it. }
  case Character.ArmorType of
    0: ArmorProtection := 0;
    1: ArmorProtection := 5;
    2: ArmorProtection := 10;
    3: ArmorProtection := 15;
    4: ArmorProtection := 25;
    5: ArmorProtection := 40
  end;

  if ArmorTreatmentPrice = MagicTreatmentDone then
    ArmorProtection :=
      ArmorProtection + Round(ArmorProtection * 0.5);

  case Character.ShieldType of
    1: ArmorProtection := ArmorProtection + 5;
    2: ArmorProtection := ArmorProtection + 10
  end;

  I := 1;
  while I <= Character.MagicCount do
  begin
    if Character.MagicItems[I] = MagicCloak then
    begin
      ArmorProtection := ArmorProtection + 10;
      I := 45
    end
    else
      I := I + 1
  end;

  case Character.BladeType of
    0: BladeDamage := 0;
    1: BladeDamage := 2;
    2: BladeDamage := 4;
    3: BladeDamage := 10;
    4: BladeDamage := 20;
    5: BladeDamage := 40
  end;

  if BladeTreatmentPrice = MagicTreatmentDone then
    BladeDamage :=
      BladeDamage + Round(BladeDamage * 0.5);

  BladeDamage := BladeDamage + Character.Strength
end;
{$R-}
