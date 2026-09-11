program NORMAL84;

{ CAVEQUEST v1.1 Stage 84 post-build normalizer.

  Stage 83/84 reproduces every deterministic byte of the original
  22-Sep-1985 QUEST.COM and reproduces QUEST.000 exactly.

  Turbo Pascal 3 writes two compiler-environment segment words into
  the program startup record, and its runtime image also contains a
  two-byte scratch word whose initial contents depend on the compiler
  session.  These six bytes are not Cavequest source/code differences.

  Run this program after compiling QUEST.PAS if a byte-for-byte copy
  of the archived 1985 QUEST.COM is desired.
}

var
  F : file;
  B : array[1..4] of byte;
  N : integer;

procedure PutBytes(Pos, Count : integer);
begin
  Seek(F, Pos);
  BlockWrite(F, B, Count, N);
  if N <> Count then begin
    WriteLn('Write error at offset ', Pos);
    Halt
  end
end;

begin
  Assign(F, 'QUEST.COM');
  {$I-}
  Reset(F, 1);
  {$I+}
  if IOResult <> 0 then begin
    WriteLn('Cannot open QUEST.COM');
    Halt
  end;

  { Runtime scratch word at file offset $0092. }
  B[1] := $78;
  B[2] := $00;
  PutBytes($0092, 2);

  { TP3 initmem inline turbocs/turbods words at $2BBB..$2BBE. }
  B[1] := $10;
  B[2] := $06;
  B[3] := $C3;
  B[4] := $0F;
  PutBytes($2BBB, 4);

  Close(F);
  WriteLn('QUEST.COM normalized to the original 1985 environment bytes.');
end.
