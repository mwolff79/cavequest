{$R+}
overlay procedure OvRuntimeInitialize;
begin
  CurrentRoom := 1;
  PreviousRoom := 1;

  InitWallGlyphIndex := 1;
  InitWallGlyphs[1] := $80;
  InitWallGlyphs[2] := $85;
  InitWallGlyphs[3] := $8D;
  InitWallGlyphs[4] := $9E;
  InitWallGlyphs[5] := $EE;
  InitWallGlyphs[6] := $F2;
  InitWallGlyphs[7] := $FE;

  Facing := InitDirNorth;

  InitDirWest  := 1;
  InitDirNorth := 2;
  InitDirEast  := 3;
  InitDirSouth := 4;

  InitDrawFlag  := true;
  InitEraseFlag := false;

  InitCmdWest  := $E6;
  InitCmdNorth := $E7;
  InitCmdEast  := $E8;
  InitCmdSouth := $E9;
  InitCmdNone  := $F0;

  MonsterY := 93;
  MonsterX := 76;
  MonsterPresent := false;

  Health     := 100;
  Restedness := 100;
  TotalSlain := 0;
  CaveTick   := 0;

  InitBlank16 := '                ';

  Ch := 'N';

  InitWeaponSword := 1;
  InitWeaponSpear := 2;
  InitWeaponBow   := 3;

  CurrentWeapon := InitWeaponSword
end;
{$R-}
