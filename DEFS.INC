const
  CharacterRecordSize = 145;
  RoomRecordSize      = 34;

  DirWest  = 1;
  DirNorth = 2;
  DirEast  = 3;
  DirSouth = 4;

  MagicCloak       = 1;
  MagicTalisman    = 2;
  MagicLightBurst  = 3;
  MagicFireBall    = 4;
  MagicEssence     = 5;
  MagicKort        = 6;
  MagicZeusRing    = 7;
  MagicMerlinCap   = 8;
  MagicEliakim     = 9;
  MagicGigos       = 10;
  MagicSalt        = 11;

  ShieldNone  = 0;
  ShieldSmall = 1;
  ShieldLarge = 2;

  ArmorNone         = 0;
  ArmorLeather      = 1;
  ArmorRingMail     = 2;
  ArmorChainMail    = 3;
  ArmorPartialPlate = 4;
  ArmorFullPlate    = 5;

  BladeNone       = 0;
  BladeKnife      = 1;
  BladeDagger     = 2;
  BladeShortSword = 3;
  BladeBroadSword = 4;
  BladeGreatSword = 5;

  AttrIntelligence = 1;
  AttrCharisma     = 2;
  AttrStrength     = 3;
  AttrDexterity    = 4;
  AttrStamina      = 5;
  AttrWizard       = 6;
  AttrLeave        = 7;

  ArmLeather       = 1;
  ArmRingMail      = 2;
  ArmChainMail     = 3;
  ArmPartialPlate  = 4;
  ArmFullPlate     = 5;
  ArmArrow         = 6;
  ArmSpear         = 7;
  ArmBow           = 8;
  ArmKnife         = 9;
  ArmDagger        = 10;
  ArmShortSword    = 11;
  ArmBroadSword    = 12;
  ArmGreatSword    = 13;
  ArmSmallShield   = 14;
  ArmLargeShield   = 15;
  ArmLeave         = 16;

  WitchMagicArmor = 1;
  WitchMagicBlade = 2;
  WitchMagicArrow = 3;
  WitchMagicSpear = 4;
  WitchLeave      = 5;
  WitchCloak      = 6;
  WitchTalisman   = 7;
  WitchLightBurst = 8;
  WitchFireBall   = 9;
  WitchEssence    = 10;
  WitchKort       = 11;
  WitchZeusRing   = 12;
  WitchMerlinCap  = 13;
  WitchEliakim    = 14;
  WitchGigos      = 15;
  WitchSalt       = 16;
  WitchPotion     = 17;

  MagicTreatmentDone = 9999;

  WeaponSword = 1;
  WeaponSpear = 2;
  WeaponBow   = 3;

  CmdWest  = $E6;
  CmdNorth = $E7;
  CmdEast  = $E8;
  CmdSouth = $E9;
  CmdNone  = 0;

type
  { TP3 requires named string types in formal parameters and SizeOf. }
  TNameString       = string[8];
  TFileName         = string[14];
  TStatusFileName   = string[12];
  TMessageString    = string[80];
  TBottomLineString = string[40];
  TTwoDigitString   = string[2];
  TNumberString  = string[3];
  TMonsterString = string[16];
  TMagicItemString = string[20];
  TTreasureString  = string[16];
  TBlank16String = string[16];

  TCharacterRecord = packed record
    Name          : TNameString;             { $00..$08 }
    Silver        : real;                    { $09..$0E }
    LifePoints    : real;                    { $0F..$14 }

    Intelligence  : byte;                    { $15 }
    Charisma      : byte;                    { $16 }
    Strength      : byte;                    { $17 }
    Dexterity     : byte;                    { $18 }
    Stamina       : byte;                    { $19 }
    WizardSkills  : byte;                    { $1A }

    Weight        : integer;                 { $1B..$1C }
    Potions       : integer;                 { $1D..$1E }
    Arrows        : integer;                 { $1F..$20 }
    MagicArrows   : integer;                 { $21..$22 }
    Spears        : integer;                 { $23..$24 }
    MagicSpears   : integer;                 { $25..$26 }

    ShieldType    : byte;                    { $27 }
    ArmorType     : byte;                    { $28 }
    BladeType     : byte;                    { $29 }
    BowOwned      : boolean;                 { $2A }

    MagicItems    : array[1..40] of byte;    { $2B..$52 }
    Treasures     : array[1..60] of byte;    { $53..$8E }

    MagicCount    : byte;                    { $8F }
    TreasureCount : byte;                    { $90 }
  end;

  TCharacterFile = file of TCharacterRecord;

  TRoom = packed record
    TopCell    : byte;                       { 00 }
    LeftCell   : byte;                       { 01 }
    BottomCell : byte;                       { 02 }
    RightCell  : byte;                       { 03 }

    WestDoorFirst  : byte;                   { 04 }
    WestDoorLast   : byte;                   { 05 }
    NorthDoorFirst : byte;                   { 06 }
    NorthDoorLast  : byte;                   { 07 }
    EastDoorFirst  : byte;                   { 08 }
    EastDoorLast   : byte;                   { 09 }
    SouthDoorFirst : byte;                   { 10 }
    SouthDoorLast  : byte;                   { 11 }

    TreasureType  : byte;                    { 12 }
    TreasureYCell : byte;                    { 13 }
    TreasureXCell : byte;                    { 14 }

    Reserved15 : byte;
    Reserved16 : byte;
    Reserved17 : byte;

    GuardMonsterType  : byte;                { 18 }
    GuardMonsterCount : byte;                { 19 }
    WanderMonsterType : byte;                { 20 }
    WanderChance500   : byte;                { 21 }

    WestRoom  : byte;                        { 22 }
    NorthRoom : byte;                        { 23 }
    EastRoom  : byte;                        { 24 }
    SouthRoom : byte;                        { 25 }

    SecretWest  : boolean;                   { 26 }
    SecretNorth : boolean;                   { 27 }
    SecretEast  : boolean;                   { 28 }
    SecretSouth : boolean;                   { 29 }

    SameScreenRoom : array[1..4] of byte;    { 30..33 }
  end;

  TSprite = packed array[0..63] of byte;

  TRoomArray       = array[1..60] of TRoom;
  TMonsterSprites  = array[1..640] of byte;
  TPlayerSprites   = array[1..768] of byte;
  TByteDefFile      = file of byte;
  TLevelDefFile     = file of TRoomArray;
  TCgaBank          = array[1..100,1..80] of byte;

var
  { Original QUEST.COM global-data order, reconstructed from address operands. }

  Rooms          : TRoomArray;              { $0260..$0A57 }

  CurrentRoom    : byte;                    { $0A58 }
  PreviousRoom   : byte;                    { $0A59 }

  LevelDefFile   : TLevelDefFile;           { $0A5A..$0AA5 }

  InitWallGlyphIndex : byte;                { $0AA6 }
  InitWallGlyphs     : array[1..7] of byte; { $0AA7..$0AAD }

  Facing         : byte;                    { $0AAE }

  InitDirWest, InitDirNorth,
  InitDirEast, InitDirSouth : byte;         { $0AAF..$0AB2 }

  InitDrawFlag, InitEraseFlag : boolean;    { $0AB3..$0AB4 }

  TreasureY, TreasureX : byte;              { $0AB5..$0AB6 }
  PlayerY, PlayerX     : byte;              { $0AB7..$0AB8 }

  PlayerSprites   : TPlayerSprites;         { $0AB9..$0DB8 }
  PlayerDefFile   : TByteDefFile;           { $0DB9..$0E04 }

  InitCmdWest, InitCmdNorth,
  InitCmdEast, InitCmdSouth,
  InitCmdNone : byte;                       { $0E05..$0E09 }

  RoomLeft, RoomTop,
  RoomRight, RoomBottom : byte;             { $0E0A..$0E0D }

  Character      : TCharacterRecord;        { $0E0E..$0E9E }

  MonsterPresent : boolean;                 { $0E9F }
  MonsterY, MonsterX : byte;                { $0EA0..$0EA1 }

  MonsterDefFile : TByteDefFile;            { $0EA2..$0EED }
  MonsterSprites : TMonsterSprites;         { $0EEE..$116D }

  BladeDamage      : byte;                  { $116E }
  ArmorProtection  : byte;                  { $116F }

  Health         : integer;                 { $1170..$1171 }
  Restedness     : integer;                 { $1172..$1173 }
  TotalSlain     : integer;                 { $1174..$1175 }
  CaveTick       : byte;                    { $1176 }

  InitBlank16    : TBlank16String;          { $1177..$1187 }

  MonsterHP      : integer;                 { $1188..$1189 }

  ProjectileY    : integer;                 { $118A..$118B }
  ProjectileX    : integer;                 { $118C..$118D }

  MonsterHostile : boolean;                 { $118E }
  SoundOn        : boolean;                 { $118F }

  SelectedLevel  : char;                    { $1190 }
  LoadedLevel    : char;                    { $1191 }

  CharacterFile  : TCharacterFile;          { $1192..$11DD }

  Ch             : char;                    { $11DE }
  PreservePlayerPosition : boolean;         { $11DF }

  CurrentWeapon  : byte;                    { $11E0 }

  InitWeaponSword, InitWeaponSpear,
  InitWeaponBow : byte;                     { $11E1..$11E3 }

  I : integer;                              { $11E4..$11E5 }

  CgaEvenBank : TCgaBank absolute $B800:$0000;
  CgaOddBank  : TCgaBank absolute $B800:$2000;


{ GraphColorMode, Palette, GraphBackground and Plot are
  native Turbo Pascal IBM-PC standard procedures.  No declarations
  are supplied here; the compiler resolves them directly. }

{$R+}
function TreasureWeight(T : byte) : byte;
begin
  case T of
     1, 6,11: TreasureWeight := 0;
     2, 7,12: TreasureWeight := 3;
     3, 8,13: TreasureWeight := 15;
     4, 9,14: TreasureWeight := 30;
     5,10,15: TreasureWeight := 50;
    16,18,20: TreasureWeight := 2;
    17       : TreasureWeight := 5;
    19       : TreasureWeight := 6;
    21       : TreasureWeight := 60
  end
end;
