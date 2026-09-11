program QUEST;

{$C-}
{ Turbo Pascal 3 defaults to C+, but the 1985 QUEST.COM startup flags
  show that Ctrl-C/Ctrl-S interpretation was compiled disabled. }

{
  CAVEQUEST v1.1 - Turbo Pascal 3 native reconstruction, Stage 84
  ----------------------------------------------------------------

  Compile to COM FILE / DISK in Turbo Pascal 3. Color 80x25 display.
  Keep this build separate from the original QUEST.COM / QUEST.000.
}
{$I DEFS.INC}
{$I TITLE.INC}
{$I LOAD.INC}
{$I ZEUS.INC}
{$I ARMORY.INC}
{$I WITCH.INC}
{$I INIT.INC}
{$I CAVE1.INC}
{$I COMBAT.INC}
{$I CAVE2.INC}
{$I CAVELOOP.INC}

{$R+}
begin
  OvRuntimeInitialize;
  OvTitleAndSound;
  OvLoadOrCreateCharacter;

  LoadedLevel := 'a';

  if OvFileAvailable('monster.def') then
  begin
    Assign(MonsterDefFile, 'monster.def');
    Reset(MonsterDefFile);

    for I := 1 to 640 do
      Read(MonsterDefFile, MonsterSprites[I]);

    Close(MonsterDefFile)
  end
  else
  begin
    writeln('Monster.def file missing from diskette.');
    halt
  end;

  if OvFileAvailable('player.def') then
  begin
    Assign(PlayerDefFile, 'player.def');
    Reset(PlayerDefFile);

    for I := 1 to 768 do
      Read(PlayerDefFile, PlayerSprites[I]);

    Close(PlayerDefFile)
  end
  else
  begin
    writeln('Player.def file missing from diskette.');
    halt
  end;

  while (Ch <> 'y') and (Ch <> 'Y') do
  begin
    if Character.LifePoints > 199 then
    begin
      OvZeusEnhancement;
      OvZeusTransport
    end;

    OvArmory;
    OvWitchesLair;

    ClrScr;
    SelectedLevel := '0';

    while (SelectedLevel < '1') or (SelectedLevel > '5') do
    begin
      writeln;
      write('Which level would you like to visit? ');
      Read(Kbd, SelectedLevel);

      if (SelectedLevel < '1') or (SelectedLevel > '5') then
      begin
        writeln;
        writeln;
        writeln('Only levels 1 thru 5 have been excavated.')
      end
    end;

    if OvFileAvailable('level' + SelectedLevel + '.def') then
    begin
      if SelectedLevel <> LoadedLevel then
      begin
        Assign(LevelDefFile, 'level' + SelectedLevel + '.def');
        Reset(LevelDefFile);
        Read(LevelDefFile, Rooms);
        LoadedLevel := SelectedLevel
      end
      else
      begin
        writeln;
        writeln;
        writeln('Ahhh, returning to the current level.');
        Delay(2000)
      end;

      TextMode(2);
      TextMode(3);
      GraphColorMode;
      Palette(0);

      OvRuntimeInitialize;
      CaveLogic;

      writeln;
      write('Do you wish to leave Cavequest? (Y/N)');
      Read(Kbd, Ch);

      Close(LevelDefFile);
      TextMode(3)
    end
    else
    begin
      writeln;
      writeln('Level ', SelectedLevel, ' is missing from the disk.');
      writeln('There must have been a cave-in!!');
      writeln;
      write('Do you wish to exit Cavequest? (Y/N)');
      Read(Kbd, Ch)
    end
  end
end.
