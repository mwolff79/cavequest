{$R+}
procedure CaveLogic;
var
  C : char;
begin
  EnterRoom;

  DrawPlayer(CurrentWeapon, InitDrawFlag);

  repeat
    C := Chr(ReadCaveCommand);

    if CaveTick = 255 then
    begin
      if Restedness < 100 then
        Restedness := Restedness + 1;

      GotoXY(38,4);
      write('   ');
      GotoXY(38,4);
      write(Restedness);

      UpdateMonster;

      CaveTick := 0;

      if Restedness = 100 then
      begin
        if Health < 100 then
          Health := Health + 1;

        GotoXY(34,3);
        write('   ');
        GotoXY(34,3);
        write(Health)
      end
    end
    else
      CaveTick := CaveTick + 1;

    with Rooms[CurrentRoom] do
    begin
      case C of
        #230:
          begin
            if SpendRestedness(2) then
            begin
              Message(' ');
              DrawPlayer(CurrentWeapon, InitEraseFlag);

              Facing := InitDirWest;
              PlayerX := PlayerX - 1;

              if PlayerX - 2 < RoomLeft then
              begin
                if (WestRoom = 0) or
                   (PlayerY + 2 < WestDoorFirst * 4) or
                   (PlayerY + 2 > (WestDoorLast - 1) * 4) or
                   SecretWest then
                begin
                  MoveSound;
                  PlayerX := PlayerX + 1
                end
                else
                begin
                  DrawMonster(GuardMonsterType, InitEraseFlag);
                  PreviousRoom := CurrentRoom;
                  CurrentRoom := WestRoom;

                  if CurrentRoom <> 255 then
                    EnterRoom
                end
              end;

              DrawPlayer(CurrentWeapon, InitDrawFlag);

              if CurrentRoom <> 255 then
                if Rooms[CurrentRoom].TreasureType > 0 then
                  DrawTreasure(InitDrawFlag)
            end
          end;

        #231:
          begin
            if SpendRestedness(2) then
            begin
              Message(' ');
              DrawPlayer(CurrentWeapon, InitEraseFlag);

              Facing := InitDirNorth;
              PlayerY := PlayerY - 2;

              if PlayerY + 1 < RoomTop then
              begin
                if (NorthRoom = 0) or
                   (PlayerX + 2 < NorthDoorFirst * 2) or
                   (PlayerX > (NorthDoorLast - 1) * 2) or
                   SecretNorth then
                begin
                  MoveSound;
                  PlayerY := PlayerY + 2
                end
                else
                begin
                  DrawMonster(GuardMonsterType, InitEraseFlag);
                  PreviousRoom := CurrentRoom;
                  CurrentRoom := NorthRoom;

                  if CurrentRoom <> 255 then
                    EnterRoom
                end
              end;

              DrawPlayer(CurrentWeapon, InitDrawFlag);

              if CurrentRoom <> 255 then
                if Rooms[CurrentRoom].TreasureType > 0 then
                  DrawTreasure(InitDrawFlag)
            end
          end;

        #232:
          begin
            if SpendRestedness(2) then
            begin
              Message(' ');
              DrawPlayer(CurrentWeapon, InitEraseFlag);

              Facing := InitDirEast;
              PlayerX := PlayerX + 1;

              if PlayerX + 2 > RoomRight then
              begin
                if (EastRoom = 0) or
                   (PlayerY + 2 < EastDoorFirst * 4) or
                   (PlayerY + 2 > (EastDoorLast - 1) * 4) or
                   SecretEast then
                begin
                  MoveSound;
                  PlayerX := PlayerX - 1
                end
                else
                begin
                  DrawMonster(GuardMonsterType, InitEraseFlag);
                  PreviousRoom := CurrentRoom;
                  CurrentRoom := EastRoom;

                  if CurrentRoom <> 255 then
                    EnterRoom
                end
              end;

              DrawPlayer(CurrentWeapon, InitDrawFlag);

              if CurrentRoom <> 255 then
                if Rooms[CurrentRoom].TreasureType > 0 then
                  DrawTreasure(InitDrawFlag)
            end
          end;

        #233:
          begin
            if SpendRestedness(2) then
            begin
              Message(' ');
              DrawPlayer(CurrentWeapon, InitEraseFlag);

              Facing := InitDirSouth;
              PlayerY := PlayerY + 2;

              if PlayerY + 10 > RoomBottom then
              begin
                if (SouthRoom = 0) or
                   (PlayerX + 2 < SouthDoorFirst * 2) or
                   (PlayerX > (SouthDoorLast - 1) * 2) or
                   SecretSouth then
                begin
                  MoveSound;
                  PlayerY := PlayerY - 2
                end
                else
                begin
                  DrawMonster(GuardMonsterType, InitEraseFlag);
                  PreviousRoom := CurrentRoom;
                  CurrentRoom := SouthRoom;

                  if CurrentRoom <> 255 then
                    EnterRoom
                end
              end;

              DrawPlayer(CurrentWeapon, InitDrawFlag);

              if CurrentRoom <> 255 then
                if Rooms[CurrentRoom].TreasureType > 0 then
                  DrawTreasure(InitDrawFlag)
            end
          end;

        'S':
          begin
            if CurrentWeapon = InitWeaponSword then
              StrikeWithBlade
            else
            begin
              DrawPlayer(CurrentWeapon, InitEraseFlag);
              CurrentWeapon := InitWeaponSword;
              DrawPlayer(CurrentWeapon, InitDrawFlag)
            end
          end;

        'A':
          begin
            if CurrentWeapon = InitWeaponBow then
              FireArrow('A')
            else
              if Character.BowOwned then
              begin
                DrawPlayer(CurrentWeapon, InitEraseFlag);
                CurrentWeapon := InitWeaponBow;
                DrawPlayer(CurrentWeapon, InitDrawFlag)
              end
              else
                Message('No bow!')
          end;

        '1':
          begin
            if CurrentWeapon = InitWeaponBow then
              FireArrow('1')
            else
              if Character.BowOwned then
              begin
                DrawPlayer(CurrentWeapon, InitEraseFlag);
                CurrentWeapon := InitWeaponBow;
                DrawPlayer(CurrentWeapon, InitDrawFlag)
              end
              else
                Message('No bow!')
          end;

        'L':
          begin
            if CurrentWeapon = InitWeaponSpear then
              LaunchSpear('L')
            else
            begin
              DrawPlayer(CurrentWeapon, InitEraseFlag);
              CurrentWeapon := InitWeaponSpear;
              DrawPlayer(CurrentWeapon, InitDrawFlag)
            end
          end;

        '0':
          begin
            if CurrentWeapon = InitWeaponSpear then
              LaunchSpear('0')
            else
            begin
              DrawPlayer(CurrentWeapon, InitEraseFlag);
              CurrentWeapon := InitWeaponSpear;
              DrawPlayer(CurrentWeapon, InitDrawFlag)
            end
          end;

        'D': DrinkHealingPotion;
        'G': GrabTreasure;
        'M': UseMagic;
        'E': ExamineSecretDoor;
        'O': OpenSecretDoor;
        'T': TalkToMonster;
        'I': ShowInventory
      end
    end;

    if CurrentRoom = 255 then
    begin
      BottomLineMessage('You are leaving the cave.  Return? (Y/N)');

      C := 'A';
      while (C <> 'y') and (C <> 'Y') and
            (C <> 'n') and (C <> 'N') do
        Read(Kbd, C);

      if (C = 'y') or (C = 'Y') then
      begin
        BottomLineMessage(' ');

        PreviousRoom := 1;
        CurrentRoom := 1
      end
      else
      begin
        TextMode(3);
        writeln('Save your character? (Y/N)');
        Read(Kbd, C);

        if (C = 'y') or (C = 'Y') then
        begin
          Assign(CharacterFile, Character.Name + '.chr');
          Rewrite(CharacterFile);
          Write(CharacterFile, Character);
          Close(CharacterFile)
        end;

        writeln;
        writeln;
        writeln('Zeus speaks!!');
        writeln;
        writeln('You have done well.');
        writeln;

        if Character.LifePoints > 199 then
          writeln('I''m taking you back to enhance yourself.')
      end
    end;

    if Health < 1 then
    begin
      Message('You''re dead!');

      if SoundOn then
      begin
        Sound(400);
        Delay(350);
        NoSound;
        Delay(20);

        Sound(400);
        Delay(350);
        NoSound;
        Delay(50);

        Sound(400);
        Delay(200);
        NoSound;
        Delay(50);

        Sound(400);
        Delay(450);
        NoSound
      end;

      Delay(3000);

      CurrentRoom := 255;

      Character.LifePoints := 0;
      Character.Silver := 0;

      for I := 1 to Character.TreasureCount do
        Character.Weight := Character.Weight -
          TreasureWeight(Character.Treasures[I]);

      Character.TreasureCount := 0;

      TextMode(3);
      GraphColorMode;

      writeln;
      writeln('Zeus speaks!!');
      writeln;
      writeln('I am very disappointed in thee,');
      writeln('but I will give thee another chance.');
      writeln;
      writeln('Your silver, life points, and');
      writeln('treasures are forfeit.');
      writeln;
      writeln('Press "C" to continue.');

      C := 'a';
      while (C <> 'c') and (C <> 'C') do
        Read(Kbd, C)
    end
  until CurrentRoom = 255
end;
{$R-}
