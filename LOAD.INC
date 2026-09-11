{$R+}
overlay function OvFileAvailable(Name : TStatusFileName) : boolean;
var
  F : file;
begin
  Assign(F, Name);

  {$I-}
  Reset(F);
  if IOResult <> 0 then
    OvFileAvailable := false
  else
  begin
    {$I+}
    Close(F);
    OvFileAvailable := true
  end
end;
{$R-}

{$R+}
overlay procedure OvLoadOrCreateCharacter;
var
  I : integer;
  C : char;
begin
  GraphColorMode;
  Palette(3);

  if SoundOn then
    for I := 20 to 550 do
    begin
      Sound(I);
      if I > 200 then
        Delay(6)
      else
        Delay(206 - I)
    end;

  for I := 1 to 7 do
  begin
    if SoundOn then Sound(586);
    GraphBackground(15);
    Delay(100);
    if SoundOn then Sound(782);
    GraphBackground(4);
    Delay(100)
  end;

  NoSound;
  GraphBackground(0);

  GotoXY(1,1);
  writeln('I have selected you, from thousands,');
  writeln('to leave the land of the gods and');
  writeln('become mortal on earth.');
  writeln;
  writeln;
  writeln('What name shall you be known by?');
  readln(Character.Name);
  writeln;
  writeln('Does your history exist on disk? (Y/N)');
  Read(Kbd, C);

  while (C <> 'Y') and (C <> 'y') and
        (C <> 'N') and (C <> 'n') do
    Read(Kbd, C);

  while (C = 'Y') or (C = 'y') do
  begin
    if OvFileAvailable(Character.Name + '.chr') then
    begin
      Assign(CharacterFile, Character.Name + '.chr');
      Reset(CharacterFile);
      Read(CharacterFile, Character);
      Close(CharacterFile);
      C := Chr(200)
    end
    else
    begin
      writeln;
      writeln('I can''t find ', Character.Name);
      writeln;
      writeln('Do you go by another name?');
      Read(Kbd, C);

      if (C = 'y') or (C = 'Y') then
      begin
        writeln;
        writeln('What name shall you be known by?');
        readln(Character.Name)
      end
    end
  end;

  if (C <> 'y') and (C <> 'Y') and (C <> #200) then
  begin
    Character.Silver     := 0;
    Character.Weight     := 0;
    Character.LifePoints := 9000;

    Character.Intelligence := 0;
    Character.Charisma     := 0;
    Character.Strength     := 0;
    Character.Dexterity    := 0;
    Character.Stamina      := 0;
    Character.WizardSkills := 0;

    Character.Potions      := 0;
    Character.Arrows       := 0;
    Character.MagicArrows  := 0;
    Character.Spears       := 0;
    Character.MagicSpears  := 0;

    Character.ShieldType := 0;
    Character.ArmorType  := 0;
    Character.BladeType  := 0;
    Character.BowOwned   := false;

    Character.MagicCount    := 0;
    Character.TreasureCount := 0
  end
end;
{$R-}
