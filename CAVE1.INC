{$R+}
procedure Message(S : TBlank16String);
begin
  GotoXY(25,9);
  write(InitBlank16);
  GotoXY(25,9);
  write(S)
end;

function SpendRestedness(ActionCost : byte) : boolean;
begin
  GotoXY(38,4);
  write('   ');

  if Character.Stamina > 0 then
    Restedness := Restedness -
                  Character.Weight div Character.Stamina div
                  Character.Stamina - ActionCost
  else
    Restedness := Restedness - Character.Weight - ActionCost;

  GotoXY(38,4);
  write(Restedness);

  if Restedness > 0 then
    SpendRestedness := true
  else
  begin
    Message('Too tired.');
    SpendRestedness := false
  end
end;
{$R-}

{$R+}
procedure DrawTreasure(DrawIt : boolean);
var
  Y, X : byte;
begin
  Y := TreasureY;
  X := TreasureX;

  if DrawIt = InitDrawFlag then
  begin
    CgaEvenBank[Y + 1, X]     := $03;
    CgaEvenBank[Y + 1, X + 1] := $C0;
    CgaOddBank [Y + 1, X]     := $0E;
    CgaOddBank [Y + 1, X + 1] := $B0;
    CgaEvenBank[Y + 2, X]     := $03;
    CgaEvenBank[Y + 2, X + 1] := $C0
  end
  else
  begin
    CgaEvenBank[Y + 1, X]     := 0;
    CgaEvenBank[Y + 1, X + 1] := 0;
    CgaOddBank [Y + 1, X]     := 0;
    CgaOddBank [Y + 1, X + 1] := 0;
    CgaEvenBank[Y + 2, X]     := 0;
    CgaEvenBank[Y + 2, X + 1] := 0
  end
end;

procedure DrawMonster(MonsterType : byte; DrawIt : boolean);
var
  Row, Col    : byte;
  SourceIndex : integer;
begin
  SourceIndex := 64 * MonsterType - 63;

  if DrawIt = InitDrawFlag then
  begin
    for Row := 0 to 7 do
    begin
      for Col := 0 to 3 do
        CgaEvenBank[MonsterY + Row, MonsterX + Col] :=
          MonsterSprites[SourceIndex + Col];

      SourceIndex := SourceIndex + 4;

      for Col := 0 to 3 do
        CgaOddBank[MonsterY + Row, MonsterX + Col] :=
          MonsterSprites[SourceIndex + Col];

      SourceIndex := SourceIndex + 4
    end
  end
  else
  begin
    for Row := 0 to 7 do
    begin
      for Col := 0 to 3 do
        CgaEvenBank[MonsterY + Row, MonsterX + Col] := 0;

      SourceIndex := SourceIndex + 4;

      for Col := 0 to 3 do
        CgaOddBank[MonsterY + Row, MonsterX + Col] := 0;

      SourceIndex := SourceIndex + 4
    end
  end
end;
{$R-}

{$R+}
function MonsterName : TMonsterString;
begin
  case Rooms[CurrentRoom].GuardMonsterType of
     1: MonsterName := 'Skeleton';
     2: MonsterName := 'Giant Bat';
     3: MonsterName := 'Giant Bug';
     4: MonsterName := 'Giant Leech';
     5: MonsterName := 'Giant Rat';
     6: MonsterName := 'Great Slime';
     7: MonsterName := 'Lizardman';
     8: MonsterName := 'Antman';
     9: MonsterName := 'Giant Squid';
    10: MonsterName := 'Zombie'
  end
end;

function MagicItemName(ItemType : byte) : TMagicItemString;
begin
  case ItemType of
     1: MagicItemName := 'Magic Cloak';
     2: MagicItemName := 'Talisman';
     3: MagicItemName := 'Light Burst';
     4: MagicItemName := 'Fire Ball';
     5: MagicItemName := 'Sphere of Essence';
     6: MagicItemName := 'Pendant of Kort';
     7: MagicItemName := 'Ring of Zeus';
     8: MagicItemName := 'Cap of Merlin';
     9: MagicItemName := 'Spell of Eliakim';
    10: MagicItemName := 'Spell of Gigos';
    11: MagicItemName := 'Magic Salt'
  end
end;

function TreasureName(T : byte) : TTreasureString;
begin
  case T of
     1: TreasureName := 'One copper';
     2: TreasureName := 'Ten coppers';
     3: TreasureName := 'Fifty coppers';
     4: TreasureName := '100 coppers';
     5: TreasureName := '1000 coppers';
     6: TreasureName := 'One silver';
     7: TreasureName := 'Ten silvers';
     8: TreasureName := 'Fifty silvers';
     9: TreasureName := '100 silvers';
    10: TreasureName := '1000 silvers';
    11: TreasureName := 'One gold';
    12: TreasureName := 'Ten gold';
    13: TreasureName := 'Fifty gold';
    14: TreasureName := '100 gold';
    15: TreasureName := '1000 gold';
    16: TreasureName := 'Small diamond';
    17: TreasureName := 'Large diamond';
    18: TreasureName := 'Emerald';
    19: TreasureName := 'Ruby';
    20: TreasureName := 'Sapphire';
    21: TreasureName := 'Copper ingot'
  end
end;

function MonsterMaxHP : byte;
begin
  MonsterMaxHP := Rooms[CurrentRoom].GuardMonsterType * 20
end;
{$R-}

{$R+}
procedure TrySpawnMonster;

  procedure MonsterArrivalSound;
  var
    I : byte;
  begin
    if SoundOn then
      for I := 1 to 50 do
      begin
        Sound(50 + Random(500));
        Delay(10)
      end;
    NoSound
  end;

begin
  with Rooms[CurrentRoom] do
  begin
    if (not MonsterPresent) and
       (GuardMonsterType = 0) and
       (WanderMonsterType <> 0) then
      if Random(500) < WanderChance500 then
      begin
        GuardMonsterType := WanderMonsterType;
        GuardMonsterCount := 1
      end;

    if GuardMonsterType <> 0 then
    begin
      MonsterHP := MonsterMaxHP;

      MonsterArrivalSound;

      MonsterY := RoomTop + 1 +
                  Random(RoomBottom - RoomTop - 11);
      MonsterX := RoomLeft + 3 +
                  Random(RoomRight - RoomLeft - 4);

      MonsterPresent := true;
      MonsterHostile := true;

      DrawMonster(GuardMonsterType, InitDrawFlag);

      GotoXY(25,7);
      write(InitBlank16);

      GotoXY(25,7);
      write(MonsterName);

      GotoXY(28,8);
      write('appears!')
    end
    else
      MonsterPresent := false
  end
end;
{$R-}

procedure DrawStatusPanel;
begin
  GotoXY(29,1);
  write(Character.Name);

  GotoXY(25,2);
  write('ROOM NUMBER: ', CurrentRoom);

  GotoXY(25,3);
  write('Health: %', Health);

  GotoXY(25,4);
  write('Restedness: %', Restedness);

  GotoXY(25,5);
  write('Weight: ', Character.Weight);

  GotoXY(25,14);
  write('Potions: ', Character.Potions);

  GotoXY(25,15);
  write('Arrows: ', Character.Arrows);

  GotoXY(25,16);
  write('Mag arrows: ', Character.MagicArrows);

  GotoXY(25,17);
  write('Spears: ', Character.Spears);

  GotoXY(25,18);
  write('Mag spears: ', Character.MagicSpears);

  GotoXY(25,20);
  write('Treasures: ', Character.TreasureCount);

  GotoXY(25,21);
  write('Magic items: ', Character.MagicCount);

  GotoXY(25,22);
  write('Total slain: ', TotalSlain);

  GotoXY(25,23);
  write('Life pts: ', Character.LifePoints:6:0)
end;

{$R+}
procedure EnterRoom;
var
  I          : byte;
  SameScreen : boolean;
begin
  SameScreen := false;

  for I := 1 to 4 do
    if Rooms[PreviousRoom].SameScreenRoom[I] = CurrentRoom then
      SameScreen := true;

  with Rooms[CurrentRoom] do
  begin
    RoomLeft   := (LeftCell - 1) * 2;
    RoomTop    := TopCell * 4;
    RoomRight  := (RightCell - 1) * 2;
    RoomBottom := BottomCell * 4;

    if not SameScreen then
    begin
      TextMode(3);
      GraphColorMode;
      DrawStatusPanel
    end
    else
    begin
      GotoXY(38,2);
      write('   ');
      GotoXY(38,2);
      write(CurrentRoom)
    end;

    if not PreservePlayerPosition then
    begin
      if Facing = InitDirWest then
      begin
        PlayerY := (EastDoorFirst +
                    ((EastDoorLast - EastDoorFirst) div 2)) * 4 - 2;
        PlayerX := RoomRight - 2
      end
      else
        if Facing = InitDirNorth then
        begin
          PlayerY := RoomBottom - 10;
          PlayerX := (SouthDoorFirst +
                      ((SouthDoorLast - SouthDoorFirst) div 2)) * 2 - 1
        end
        else
          if Facing = InitDirEast then
          begin
            PlayerY := (WestDoorFirst +
                        ((WestDoorLast - WestDoorFirst) div 2)) * 4 - 2;
            PlayerX := RoomLeft + 2
          end
          else
          begin
            PlayerY := RoomTop + 2;
            PlayerX := (NorthDoorFirst +
                        ((NorthDoorLast - NorthDoorFirst) div 2)) * 2 - 1
          end
    end;

    PreservePlayerPosition := false;

    TrySpawnMonster;

    if InitWallGlyphIndex = 7 then
      InitWallGlyphIndex := 1
    else
      InitWallGlyphIndex := InitWallGlyphIndex + 1;

    GotoXY(LeftCell, TopCell);
    for I := LeftCell to RightCell do
      write(Chr(InitWallGlyphs[InitWallGlyphIndex]));

    for I := TopCell to BottomCell do
    begin
      GotoXY(RightCell, I);
      write(Chr(InitWallGlyphs[InitWallGlyphIndex]));
      GotoXY(LeftCell, I);
      write(Chr(InitWallGlyphs[InitWallGlyphIndex]))
    end;

    { The original relies on the cursor position left by the final
      vertical-wall write to finish the bottom wall. }
    for I := LeftCell to RightCell - 1 do
      write(Chr(InitWallGlyphs[InitWallGlyphIndex]));

    if (not SecretWest) and (WestDoorFirst <> 0) then
      for I := WestDoorFirst to WestDoorLast do
      begin
        GotoXY(LeftCell, I);
        write(' ')
      end;

    if (not SecretNorth) and (NorthDoorFirst <> 0) then
    begin
      GotoXY(NorthDoorFirst, TopCell);
      for I := NorthDoorFirst to NorthDoorLast do
        write(' ')
    end;

    if (not SecretEast) and (EastDoorFirst <> 0) then
      for I := EastDoorFirst to EastDoorLast do
      begin
        GotoXY(RightCell, I);
        write(' ')
      end;

    if (not SecretSouth) and (SouthDoorFirst <> 0) then
    begin
      GotoXY(SouthDoorFirst, BottomCell);
      for I := SouthDoorFirst to SouthDoorLast do
        write(' ')
    end;

    if TreasureType > 0 then
    begin
      TreasureY := 4 * (Rooms[CurrentRoom].TreasureYCell - 1);
      TreasureX := 2 * Rooms[CurrentRoom].TreasureXCell;
      DrawTreasure(InitDrawFlag)
    end
  end
end;
{$R-}

procedure WallBumpSound;
begin
  if SoundOn then
  begin
    Sound(80);
    Delay(30);
    Sound(60);
    Delay(30);
    NoSound
  end
end;

{$R+}
procedure DrawPlayer(WeaponType : byte; DrawIt : boolean);
var
  I, J        : byte;
  SourceIndex : integer;
begin
  if DrawIt = InitDrawFlag then
    WallBumpSound;

  if WeaponType = InitWeaponSword then
    SourceIndex := Facing * 64 - 63
  else
    if WeaponType = InitWeaponSpear then
      SourceIndex := Facing * 64 + 193
    else
      SourceIndex := Facing * 64 + 449;

  if DrawIt = InitDrawFlag then
  begin
    for I := 0 to 7 do
    begin
      for J := 0 to 3 do
        CgaEvenBank[PlayerY + I, PlayerX + J] :=
          PlayerSprites[SourceIndex + J];

      SourceIndex := SourceIndex + 4;

      for J := 0 to 3 do
        CgaOddBank[PlayerY + I, PlayerX + J] :=
          PlayerSprites[SourceIndex + J];

      SourceIndex := SourceIndex + 4
    end
  end
  else
  begin
    for I := 0 to 7 do
    begin
      for J := 0 to 3 do
        CgaEvenBank[PlayerY + I, PlayerX + J] := 0;

      SourceIndex := SourceIndex + 4;

      for J := 0 to 3 do
        CgaOddBank[PlayerY + I, PlayerX + J] := 0;

      SourceIndex := SourceIndex + 4
    end
  end
end;
{$R-}

{$R+}
function ReadCaveCommand : byte;
var
  C, C2 : char;
begin
  ReadCaveCommand := InitCmdNone;

  if KeyPressed then
  begin
    Read(Kbd, C);
    ReadCaveCommand := Ord(UpCase(C))
  end;

  if (C = #27) and KeyPressed then
  begin
    Read(Kbd, C2);

    case C2 of
      'K': ReadCaveCommand := InitCmdWest;
      'H': ReadCaveCommand := InitCmdNorth;
      'M': ReadCaveCommand := InitCmdEast;
      'P': ReadCaveCommand := InitCmdSouth
    end
  end
end;
{$R-}

procedure MoveSound;
begin
  if SoundOn then
  begin
    Sound(450);
    Delay(75);
    NoSound
  end
end;

{$R+}
procedure ExamineSecretDoor;
var
  I : byte;

  procedure SecretDoorSound;
  begin
    if SoundOn then
    begin
      Sound(300); Delay(200);
      Sound(200); Delay(150);
      NoSound;
      Sound(200); Delay(250);
      Sound(300); Delay(200);
      Sound(500); Delay(600);
      NoSound
    end
  end;

begin
  if SpendRestedness(4) then
    if Character.Intelligence > Random(18) then
      with Rooms[CurrentRoom] do
      begin
        if (Facing = InitDirWest) and SecretWest then
        begin
          Message('A SECRET DOOR!!');
          SecretDoorSound;

          for I := WestDoorFirst to WestDoorLast do
          begin
            GotoXY(LeftCell, I);
            write('#')
          end
        end
        else
          if (Facing = InitDirNorth) and SecretNorth then
          begin
            Message('A SECRET DOOR!!');
            SecretDoorSound;

            GotoXY(NorthDoorFirst, TopCell);
            for I := NorthDoorFirst to NorthDoorLast do
              write('#')
          end
          else
            if (Facing = InitDirEast) and SecretEast then
            begin
              Message('A SECRET DOOR!!');
              SecretDoorSound;

              for I := EastDoorFirst to EastDoorLast do
              begin
                GotoXY(RightCell, I);
                write('#')
              end
            end
            else
              if (Facing = InitDirSouth) and SecretSouth then
              begin
                Message('A SECRET DOOR!!');
                SecretDoorSound;

                GotoXY(SouthDoorFirst, BottomCell);
                for I := SouthDoorFirst to SouthDoorLast do
                  write('#')
              end
              else
              begin
                Message('Nothing found.')
              end
      end
    else
    begin
      Message('Nothing found.')
    end
end;
{$R-}

{$R+}
procedure OpenSecretDoor;
var
  I : byte;

  procedure DoorOpenSound;
  var
    J : byte;
  begin
    if SoundOn then
      for J := 1 to 100 do
      begin
        Sound(50 + Random(5));
        Delay(10)
      end;
    NoSound
  end;

begin
  if SpendRestedness(5) then
    if Character.Intelligence > Random(18) then
      with Rooms[CurrentRoom] do
      begin
        if (Facing = InitDirWest) and SecretWest and
           (PlayerX < (LeftCell + 1) * 2) then
        begin
          DoorOpenSound;
          SecretWest := false;

          for I := WestDoorFirst to WestDoorLast do
          begin
            GotoXY(LeftCell, I);
            write(' ')
          end
        end
        else
          if (Facing = InitDirNorth) and SecretNorth and
             (PlayerY < (TopCell + 1) * 4) then
          begin
            DoorOpenSound;
            SecretNorth := false;

            GotoXY(NorthDoorFirst, TopCell);
            for I := NorthDoorFirst to NorthDoorLast do
              write(' ')
          end
          else
            if (Facing = InitDirEast) and SecretEast and
               (PlayerX > (RightCell - 3) * 2) then
            begin
              DoorOpenSound;
              SecretEast := false;

              for I := EastDoorFirst to EastDoorLast do
              begin
                GotoXY(RightCell, I);
                write(' ')
              end
            end
            else
              if (Facing = InitDirSouth) and SecretSouth and
                 (PlayerY > (BottomCell - 1) * 2) then
              begin
                DoorOpenSound;
                SecretSouth := false;

                GotoXY(SouthDoorFirst, BottomCell);
                for I := SouthDoorFirst to SouthDoorLast do
                  write(' ')
              end
              else
              begin
                Message('Can''t open door.')
              end
      end
    else
    begin
      Message('Can''t open door.')
    end
end;
{$R-}

{$R+}
procedure GrabTreasure;
var
  I : byte;
begin
  MonsterHostile := true;

  if (PlayerY - 4 < TreasureY) and
     (PlayerY + 4 > TreasureY) and
     (PlayerX - 4 < TreasureX) and
     (PlayerX + 4 > TreasureX) and
     (Rooms[CurrentRoom].TreasureType > 0) and
     SpendRestedness(1) then
  begin
    if SoundOn then
      for I := 1 to 5 do
      begin
        Sound(685);
        Delay(50);
        Sound(885);
        Delay(50)
      end;
    NoSound;

    DrawTreasure(InitEraseFlag);

    Character.TreasureCount := Character.TreasureCount + 1;
    Character.Treasures[Character.TreasureCount] :=
      Rooms[CurrentRoom].TreasureType;
    Rooms[CurrentRoom].TreasureType := 0;

    Message(TreasureName(
      Character.Treasures[Character.TreasureCount]));

    GotoXY(36,20);
    write(Character.TreasureCount);

    Character.LifePoints := Character.LifePoints + 20;
    GotoXY(35,23);
    write(Character.LifePoints:6:0);

    Character.Weight := Character.Weight +
      TreasureWeight(Character.Treasures[Character.TreasureCount]);

    GotoXY(33,5);
    write(Character.Weight)
  end
  else
    Message('Can''t grab it.')
end;
{$R-}
