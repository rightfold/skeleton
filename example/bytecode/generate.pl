#!/usr/bin/env perl

use strict;
use warnings;

use constant NoOp     => 0x00;
use constant Break    => 0x01;
use constant Call     => 0x11;
use constant Return   => 0x12;
use constant Allocate => 0x30;

sub uint16 { print pack('v', shift); }
sub uint32 { print pack('V', shift); }
sub uint64 { print pack('VV', $_[0] & 0xFFFFFFFF, $_[0] >> 32); }

sub instruction
{
    uint16(shift);
    uint16(shift);
    uint32(shift);
    uint64(shift);
}

sub subroutine
{
    uint32(shift);
    uint32(shift);
}

uint64(12);
uint64(2);

instruction(NoOp,     0, 0, 0);
instruction(Break,    0, 0, 0);
instruction(Call,     0, 0, 1);
instruction(Break,    0, 0, 0);
instruction(Return,   0, 0, 0);

instruction(NoOp,     0, 0, 0);
instruction(Break,    0, 0, 0);
instruction(Allocate, 0, 0, 0);
instruction(Break,    0, 0, 0);
instruction(Allocate, 0, 0, 1 << 32);
instruction(Break,    0, 0, 0);
instruction(Return,   0, 0, 0);

subroutine(0, 1);
subroutine(5, 1);
