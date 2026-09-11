{$R+}
procedure TalkToMonster;
var
  I : byte;
begin
  if SpendRestedness(1) then
    if MonsterPresent then
    begin
      for I := 1 to 200 do
      begin
        if SoundOn then
          Sound(Random(800));
        Delay(20)
      end;
      NoSound;

      if Random(19) > Character.Charisma then
      begin
        GotoXY(25,10);
        write(InitBlank16);
        GotoXY(25,10);
        write('Kill thee!');
        MonsterHostile := true
      end
      else
      begin
        GotoXY(25,10);
        write(InitBlank16);
        GotoXY(25,10);
        write('Pass!!');
        MonsterHostile := false
      end
    end
    else
    begin
      Message('No monsters.')
    end
end;
{$R-}

{$R+}
procedure ShowInventory;
var
  I : byte;
  C : char;
begin
  PreservePlayerPosition := true;

  TextMode(3);
  TextColor(15);
  TextBackground(0);

  GotoXY(35,1);
  writeln('TREASURES');
  writeln;

  for I := 1 to 22 do
    if Character.TreasureCount >= I then
      writeln(I, '  ', TreasureName(Character.Treasures[I]));

  for I := 23 to 44 do
    if Character.TreasureCount >= I then
    begin
      GotoXY(27, I - 20);
      write(I, '  ', TreasureName(Character.Treasures[I]))
    end;

  for I := 45 to 60 do
    if Character.TreasureCount >= I then
    begin
      GotoXY(53, I - 42);
      write(I, '  ', TreasureName(Character.Treasures[I]))
    end;

  GotoXY(1,25);
  TextColor(4 + 16);
  write('Press any key.');
  Read(Kbd, C);

  TextColor(15);
  ClrScr;

  GotoXY(34,1);
  writeln('MAGIC ITEMS');
  writeln;

  for I := 1 to 22 do
    if Character.MagicCount >= I then
      writeln(I, '  ', MagicItemName(Character.MagicItems[I]));

  for I := 23 to 40 do
    if Character.MagicCount >= I then
    begin
      GotoXY(40, I - 20);
      write(I, '  ', MagicItemName(Character.MagicItems[I]))
    end;

  GotoXY(1,25);
  TextColor(4 + 16);
  write('Press any key.');
  Read(Kbd, C);

  TextMode(2);
  TextMode(3);
  GraphColorMode;
  Palette(0);

  PreviousRoom := CurrentRoom;
  EnterRoom;
  DrawPlayer(CurrentWeapon, InitDrawFlag);
  DrawStatusPanel
end;
{$R-}

{$R+}
procedure BottomLineMessage(S : TBottomLineString);
begin
  GotoXY(1,25);
  write('                                        ');
  GotoXY(1,25);
  write(S)
end;
{$R-}

{$R+}
procedure UseMagic;
var
  I               : byte;
  S               : TTwoDigitString;
  InventoryNumber : integer;
  Code            : integer;
  Item            : byte;
  OldIntelligence : byte;
  OldFacing       : byte;
  C1, C2          : char;

  procedure MagicSound;
  var
    J : byte;
  begin
    if SoundOn then
      for J := 1 to 4 do
      begin
        Sound(800);
        Delay(200);
        Sound(900);
        Delay(200);
        Sound(800);
        Delay(200);
        Sound(700);
        Delay(200)
      end;
    NoSound
  end;

  procedure UseMagicItem(ItemWeight : byte);
  begin
    for I := InventoryNumber to Character.MagicCount - 1 do
      Character.MagicItems[I] := Character.MagicItems[I + 1];

    Character.MagicCount := Character.MagicCount - 1;

    GotoXY(38,21);
    write('   ');
    GotoXY(38,21);
    write(Character.MagicCount);

    Character.Weight := Character.Weight - ItemWeight;

    GotoXY(33,5);
    write('   ');
    GotoXY(33,5);
    write(Character.Weight)
  end;

begin
  BottomLineMessage('Inventory number (two digits)? __');

  GotoXY(32,25);
  Read(Kbd, C1);
  if C1 <> #13 then
    write(C1);

  Read(Kbd, C2);
  if C2 <> #13 then
    write(C2);

  S := C1 + C2;
  Val(S, InventoryNumber, Code);

  if SpendRestedness(3) then
    if Code = 0 then
    begin
      if (InventoryNumber < 1) or
         (InventoryNumber > Character.MagicCount) then
        BottomLineMessage('You have no number ' + S)
      else
      begin
        Item := Character.MagicItems[InventoryNumber];

        BottomLineMessage('Using ' + MagicItemName(Item));

        case Item of
          MagicCloak:
            BottomLineMessage('The Magic Cloak is automatic');

          MagicTalisman:
            if Character.WizardSkills > 7 then
            begin
              MagicSound;

              if Rooms[CurrentRoom].WanderChance500 > 19 then
                Rooms[CurrentRoom].WanderChance500 :=
                  Rooms[CurrentRoom].WanderChance500 - 20
              else
                Rooms[CurrentRoom].WanderChance500 := 0
            end;

          MagicLightBurst:
            if Character.WizardSkills > 0 then
            begin
              MagicSound;
              MonsterHostile := false;
              UseMagicItem(2)
            end;

          MagicFireBall:
            if Character.WizardSkills > 7 then
            begin
              MagicSound;
              if MonsterPresent then
                DamageMonster(100);
              UseMagicItem(10)
            end;

          MagicEssence:
            if Character.WizardSkills > 6 then
            begin
              MagicSound;
              if MonsterPresent then
                DamageMonster(50)
            end;

          MagicKort:
            if Character.WizardSkills > 17 then
            begin
              MagicSound;
              if MonsterPresent and
                 (Rooms[CurrentRoom].GuardMonsterType = 10) then
                DamageMonster(200)
            end;

          MagicZeusRing:
            if Character.WizardSkills > 14 then
            begin
              MagicSound;

              if MonsterPresent and
                 (Rooms[CurrentRoom].GuardMonsterType > 2) then
              begin
                DrawMonster(Rooms[CurrentRoom].GuardMonsterType,
                            InitEraseFlag);
                MonsterPresent := false;
                Rooms[CurrentRoom].GuardMonsterType :=
                  Rooms[CurrentRoom].GuardMonsterType - 2;
                TrySpawnMonster
              end
            end;

          MagicMerlinCap:
            if Character.WizardSkills > 8 then
            begin
              MagicSound;

              OldIntelligence := Character.Intelligence;
              OldFacing := Facing;

              Character.Intelligence := 20;

              Facing := InitDirWest;
              ExamineSecretDoor;
              Facing := InitDirNorth;
              ExamineSecretDoor;
              Facing := InitDirEast;
              ExamineSecretDoor;
              Facing := InitDirSouth;
              ExamineSecretDoor;

              Message(InitBlank16);

              Character.Intelligence := OldIntelligence;
              Facing := OldFacing
            end;

          MagicEliakim:
            if Character.WizardSkills > 15 then
            begin
              MagicSound;
              if MonsterPresent then
                DamageMonster(120);
              UseMagicItem(2)
            end;

          MagicGigos:
            if Character.WizardSkills > 10 then
            begin
              MagicSound;
              if MonsterPresent then
                DamageMonster(80);
              UseMagicItem(2)
            end;

          MagicSalt:
            if Character.WizardSkills > 9 then
            begin
              MagicSound;
              if MonsterPresent and
                 (Rooms[CurrentRoom].GuardMonsterType = 4) then
                DamageMonster(80);
              UseMagicItem(5)
            end
        end
      end
    end
    else
      BottomLineMessage('That is no number.');

  BottomLineMessage(' ')
end;
{$R-}

{$R+}
procedure DrinkHealingPotion;
begin
  if (Character.WizardSkills > 4) and
     (Character.Potions > 0) then
  begin
    Health := Health + Character.Stamina * 2;

    if Health > 100 then
      Health := 100;

    GotoXY(34,3);
    write('   ');
    GotoXY(34,3);
    write(Health);

    Character.Potions := Character.Potions - 1;

    GotoXY(34,14);
    write('    ');
    GotoXY(34,14);
    write(Character.Potions);

    Character.Weight := Character.Weight - 2;

    GotoXY(33,5);
    write('    ');
    GotoXY(33,5);
    write(Character.Weight)
  end
end;
{$R-}
