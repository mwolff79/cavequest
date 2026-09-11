{$R+}
procedure MoveOrAttackMonster;
var
  Speed     : byte;
  YDistance : byte;
  XDistance : byte;
  Step      : byte;
begin
  if MonsterHostile then
  begin
    case Rooms[CurrentRoom].GuardMonsterType of
       1: Speed := 1;
       2: Speed := 5;
       3: Speed := 3;
       4: Speed := 2;
       5: Speed := 4;
       6: Speed := 1;
       7: Speed := 6;
       8: Speed := 8;
       9: Speed := 7;
      10: Speed := 10
    end;

    YDistance := Abs(PlayerY - MonsterY);
    XDistance := Abs(PlayerX - MonsterX);

    if (YDistance <> 0) or (XDistance <> 0) then
    begin
      DrawMonster(Rooms[CurrentRoom].GuardMonsterType, InitEraseFlag);

      if YDistance >= XDistance then
      begin
        if YDistance >= Speed then
          Step := Speed
        else
          Step := YDistance;

        if PlayerY >= MonsterY then
          MonsterY := MonsterY + Step
        else
          MonsterY := MonsterY - Step
      end
      else
      begin
        if XDistance >= Speed then
          Step := Speed
        else
          Step := XDistance;

        if PlayerX >= MonsterX then
          MonsterX := MonsterX + Step
        else
          MonsterX := MonsterX - Step
      end;

      WallBumpSound;

      DrawMonster(Rooms[CurrentRoom].GuardMonsterType, InitDrawFlag);

      if Rooms[CurrentRoom].TreasureType > 0 then
      begin
        DrawTreasure(InitDrawFlag)
      end
    end
    else
      if Random(MonsterHP + 1) > ArmorProtection then
      begin
        if SoundOn then
          Sound(800);

        GotoXY(25,11);
        write(InitBlank16);
        GotoXY(25,11);
        write('Hit thee!!');

        GraphBackground(4);
        Delay(20);
        GraphBackground(0);

        Health := Health - MonsterHP + ArmorProtection;

        GotoXY(34,3);
        write('   ');
        GotoXY(34,3);
        write(Health);

        NoSound
      end
      else
      begin
        GotoXY(25,11);
        write(InitBlank16);
        GotoXY(25,11);
        write('No injury!')
      end
  end
end;
{$R-}

procedure UpdateMonster;
begin
  if MonsterPresent then
  begin
    MoveOrAttackMonster
  end
  else
  begin
    TrySpawnMonster
  end
end;

{$R+}
procedure DamageMonster(Damage : byte);
begin
  Message('You hit ''im!!');

  MonsterHP := MonsterHP - Damage;
  MonsterHostile := true;

  if MonsterHP < 1 then
  begin
    GotoXY(25,8);
    write(InitBlank16);
    GotoXY(25,7);
    write(InitBlank16);
    GotoXY(25,7);
    write('Monster killed.');

    MonsterPresent := false;

    DrawMonster(Rooms[CurrentRoom].GuardMonsterType, InitEraseFlag);

    Character.LifePoints := Character.LifePoints + MonsterMaxHP;
    GotoXY(35,23);
    write(Character.LifePoints:6:0);

    TotalSlain := TotalSlain + 1;
    GotoXY(38,22);
    write(TotalSlain);

    Rooms[CurrentRoom].GuardMonsterCount :=
      Rooms[CurrentRoom].GuardMonsterCount - 1;

    if Rooms[CurrentRoom].GuardMonsterCount = 0 then
      Rooms[CurrentRoom].GuardMonsterType := 0;

    DrawPlayer(CurrentWeapon, InitDrawFlag);

    if Rooms[CurrentRoom].TreasureType > 0 then
    begin
      DrawTreasure(InitDrawFlag)
    end
  end
end;
{$R-}

{$R+}
procedure StrikeWithBlade;
var
  YDistance : byte;
  XDistance : byte;

  procedure BladeStrikeSound;
  begin
    if SoundOn then
    begin
      Sound(1100);
      Delay(100);
      Sound(900);
      Delay(100);
      NoSound
    end
  end;

begin
  YDistance := Abs(PlayerY - MonsterY);
  XDistance := Abs(PlayerX - MonsterX);

  if SpendRestedness(5) then
    if MonsterPresent then
      if (YDistance < 7) and (XDistance < 5) then
        if ((Facing = InitDirWest) and (MonsterX <= PlayerX)) or
           ((Facing = InitDirNorth) and (MonsterY <= PlayerY)) or
           ((Facing = InitDirEast) and (MonsterX >= PlayerX)) or
           ((Facing = InitDirSouth) and (MonsterY >= PlayerY)) then
        begin
          BladeStrikeSound;
          DamageMonster(BladeDamage)
        end
        else
          Message('Wrong direction.')
      else
        Message('Too far.')
    else
      Message('No monsters.')
end;
{$R-}

{$R+}
procedure FireArrow(Command : char);
var
  YDistance      : byte;
  XDistance      : byte;
  StopProjectile : boolean;

  procedure ArrowSound;
  var
    I : integer;
  begin
    if SoundOn then
    begin
      Sound(1100);
      Delay(30);
      for I := 800 downto 400 do
        Sound(I);
      NoSound
    end
  end;

  procedure DrawArrow(DrawIt : boolean);
  var
    Y : byte;
    X : byte;
  begin
    Y := ProjectileY;
    X := ProjectileX;

    if (Facing = InitDirWest) or (Facing = InitDirEast) then
    begin
      if DrawIt = InitDrawFlag then
      begin
        CgaOddBank[Y + 3, X + 1] := $AA;
        CgaOddBank[Y + 3, X + 2] := $AA
      end
      else
      begin
        CgaOddBank[Y + 3, X + 1] := 0;
        CgaOddBank[Y + 3, X + 2] := 0
      end
    end
    else
    begin
      if DrawIt = InitDrawFlag then
      begin
        CgaEvenBank[Y + 2, X + 1] := 2;
        CgaOddBank [Y + 2, X + 1] := 2;
        CgaEvenBank[Y + 3, X + 1] := 2;
        CgaOddBank [Y + 3, X + 1] := 2;
        CgaEvenBank[Y + 4, X + 1] := 2;
        CgaOddBank [Y + 4, X + 1] := 2;
        CgaEvenBank[Y + 5, X + 1] := 2;
        CgaOddBank [Y + 5, X + 1] := 2
      end
      else
      begin
        CgaEvenBank[Y + 2, X + 1] := 0;
        CgaOddBank [Y + 2, X + 1] := 0;
        CgaEvenBank[Y + 3, X + 1] := 0;
        CgaOddBank [Y + 3, X + 1] := 0;
        CgaEvenBank[Y + 4, X + 1] := 0;
        CgaOddBank [Y + 4, X + 1] := 0;
        CgaEvenBank[Y + 5, X + 1] := 0;
        CgaOddBank [Y + 5, X + 1] := 0
      end
    end
  end;

begin
  StopProjectile := false;

  if SpendRestedness(1) then
    if ((((Command = 'A') and (Character.Arrows > 0)) or
         ((Command = '1') and (Character.MagicArrows > 0))) and
        Character.BowOwned) then
    begin
      ArrowSound;

      if Facing = InitDirWest then
      begin
        ProjectileY := PlayerY;
        ProjectileX := PlayerX - 2
      end
      else
        if Facing = InitDirNorth then
        begin
          ProjectileY := PlayerY - 8;
          ProjectileX := PlayerX
        end
        else
          if Facing = InitDirEast then
          begin
            ProjectileY := PlayerY;
            ProjectileX := PlayerX + 2
          end
          else
          begin
            ProjectileY := PlayerY + 5;
            ProjectileX := PlayerX
          end;

      if ProjectileY < 4 then
        ProjectileY := 4;
      if ProjectileX < 2 then
        ProjectileX := 2;

      repeat
        DrawArrow(InitEraseFlag);

        if Facing = InitDirWest then
          ProjectileX := ProjectileX - 1
        else
          if Facing = InitDirNorth then
            ProjectileY := ProjectileY - 2
          else
            if Facing = InitDirEast then
              ProjectileX := ProjectileX + 1
            else
              ProjectileY := ProjectileY + 2;

        DrawArrow(InitDrawFlag);
        Delay(15);

        if MonsterPresent then
        begin
          YDistance := Abs(MonsterY - ProjectileY);
          XDistance := Abs(MonsterX - ProjectileX)
        end
        else
        begin
          YDistance := 255;
          XDistance := 255
        end;

        if ((Facing = InitDirWest) and
            (ProjectileX - 4 < RoomLeft)) or
           ((Facing = InitDirNorth) and
            (ProjectileY - 2 < RoomTop)) or
           ((Facing = InitDirEast) and
            (ProjectileX + 4 > RoomRight)) or
           ((Facing = InitDirSouth) and
            (ProjectileY + 12 > RoomBottom)) then
          StopProjectile := true
      until ((YDistance < 4) and (XDistance < 5)) or StopProjectile;

      DrawArrow(InitEraseFlag);

      if (YDistance < 4) and (XDistance < 5) and
         (Random(18) < Character.Dexterity) then
      begin
        if Command = 'A' then
          DamageMonster(20)
        else
          DamageMonster(50)
      end
      else
        Message('Missed!');

      Character.Weight := Character.Weight - 1;
      GotoXY(33,5);
      write('    ');
      GotoXY(33,5);
      write(Character.Weight);

      if Command = 'A' then
      begin
        Character.Arrows := Character.Arrows - 1;
        GotoXY(33,15);
        write('    ');
        GotoXY(33,15);
        write(Character.Arrows)
      end
      else
      begin
        Character.MagicArrows := Character.MagicArrows - 1;
        GotoXY(37,16);
        write('    ');
        GotoXY(37,16);
        write(Character.MagicArrows)
      end
    end
    else
      Message('No arrows/bow.')
end;
{$R-}

{$R+}
procedure LaunchSpear(Command : char);
var
  YDistance : byte;
  XDistance : byte;

  procedure SpearSound;
  begin
    if SoundOn then
    begin
      Sound(900);
      Delay(100);
      Sound(1100);
      Delay(100);
      NoSound
    end
  end;

  procedure DrawSpear(DrawIt : boolean);
  var
    Y : byte;
    X : byte;
  begin
    Y := ProjectileY;
    X := ProjectileX;

    if (Facing = InitDirWest) or (Facing = InitDirEast) then
    begin
      if DrawIt = InitDrawFlag then
      begin
        CgaOddBank[Y + 3, X]     := $AA;
        CgaOddBank[Y + 3, X + 1] := $AA;
        CgaOddBank[Y + 3, X + 2] := $AA;
        CgaOddBank[Y + 3, X + 3] := $AA
      end
      else
      begin
        CgaOddBank[Y + 3, X]     := 0;
        CgaOddBank[Y + 3, X + 1] := 0;
        CgaOddBank[Y + 3, X + 2] := 0;
        CgaOddBank[Y + 3, X + 3] := 0
      end
    end
    else
    begin
      if DrawIt = InitDrawFlag then
      begin
        CgaEvenBank[Y,     X + 1] := 2;
        CgaOddBank [Y,     X + 1] := 2;
        CgaEvenBank[Y + 1, X + 1] := 2;
        CgaOddBank [Y + 1, X + 1] := 2;
        CgaEvenBank[Y + 2, X + 1] := 2;
        CgaOddBank [Y + 2, X + 1] := 2;
        CgaEvenBank[Y + 3, X + 1] := 2;
        CgaOddBank [Y + 3, X + 1] := 2;
        CgaEvenBank[Y + 4, X + 1] := 2;
        CgaOddBank [Y + 4, X + 1] := 2;
        CgaEvenBank[Y + 5, X + 1] := 2;
        CgaOddBank [Y + 5, X + 1] := 2;
        CgaEvenBank[Y + 6, X + 1] := 2;
        CgaOddBank [Y + 6, X + 1] := 2;
        CgaEvenBank[Y + 7, X + 1] := 2;
        CgaOddBank [Y + 7, X + 1] := 2
      end
      else
      begin
        CgaEvenBank[Y,     X + 1] := 0;
        CgaOddBank [Y,     X + 1] := 0;
        CgaEvenBank[Y + 1, X + 1] := 0;
        CgaOddBank [Y + 1, X + 1] := 0;
        CgaEvenBank[Y + 2, X + 1] := 0;
        CgaOddBank [Y + 2, X + 1] := 0;
        CgaEvenBank[Y + 3, X + 1] := 0;
        CgaOddBank [Y + 3, X + 1] := 0;
        CgaEvenBank[Y + 4, X + 1] := 0;
        CgaOddBank [Y + 4, X + 1] := 0;
        CgaEvenBank[Y + 5, X + 1] := 0;
        CgaOddBank [Y + 5, X + 1] := 0;
        CgaEvenBank[Y + 6, X + 1] := 0;
        CgaOddBank [Y + 6, X + 1] := 0;
        CgaEvenBank[Y + 7, X + 1] := 0;
        CgaOddBank [Y + 7, X + 1] := 0
      end
    end
  end;

begin
  if SpendRestedness(2) then
    if (((Command = 'L') and (Character.Spears > 0)) or
        ((Command = '0') and (Character.MagicSpears > 0))) then
    begin
      SpearSound;

      if Facing = InitDirWest then
      begin
        ProjectileY := PlayerY;
        ProjectileX := PlayerX - 2
      end
      else
        if Facing = InitDirNorth then
        begin
          ProjectileY := PlayerY - 8;
          ProjectileX := PlayerX
        end
        else
          if Facing = InitDirEast then
          begin
            ProjectileY := PlayerY;
            ProjectileX := PlayerX + 2
          end
          else
          begin
            ProjectileY := PlayerY + 8;
            ProjectileX := PlayerX
          end;

      if ProjectileY < 4 then
        ProjectileY := 4;
      if ProjectileX < 2 then
        ProjectileX := 2;

      repeat
        DrawSpear(InitEraseFlag);

        if Facing = InitDirWest then
          ProjectileX := ProjectileX - 1
        else
          if Facing = InitDirNorth then
            ProjectileY := ProjectileY - 2
          else
            if Facing = InitDirEast then
              ProjectileX := ProjectileX + 1
            else
              ProjectileY := ProjectileY + 2;

        DrawSpear(InitDrawFlag);
        Delay(25);

        if MonsterPresent then
        begin
          YDistance := Abs(MonsterY - ProjectileY);
          XDistance := Abs(MonsterX - ProjectileX)
        end
        else
        begin
          YDistance := 255;
          XDistance := 255
        end
      until ((YDistance < 4) and (XDistance < 5)) or
            ((Facing = InitDirWest) and
             (ProjectileX - 4 < RoomLeft)) or
            ((Facing = InitDirNorth) and
             (ProjectileY - 2 < RoomTop)) or
            ((Facing = InitDirEast) and
             (ProjectileX + 4 > RoomRight)) or
            ((Facing = InitDirSouth) and
             (ProjectileY + 12 > RoomBottom));

      DrawSpear(InitEraseFlag);

      if (YDistance < 4) and (XDistance < 5) and
         (Random(18) < Character.Dexterity) then
      begin
        { Original v1.1 command-test quirk retained. }
        if Command = 'A' then
          DamageMonster(40)
        else
          DamageMonster(75)
      end
      else
        Message('Missed!');

      Character.Weight := Character.Weight - 2;
      GotoXY(33,5);
      write('    ');
      GotoXY(33,5);
      write(Character.Weight);

      if Command = 'L' then
      begin
        Character.Spears := Character.Spears - 1;
        GotoXY(33,17);
        write('    ');
        GotoXY(33,17);
        write(Character.Spears)
      end
      else
      begin
        Character.MagicSpears := Character.MagicSpears - 1;
        GotoXY(37,18);
        write('    ');
        GotoXY(37,18);
        write(Character.MagicSpears)
      end
    end
    else
      Message('No spears.')
end;
{$R-}
