# Index tools

A set of utils to work with FASTQ files with index information in definition line.

```
@HISEQ:31:C39VUACXX:4:1315:4250:31911 2:N:0:NAGATC
ATTGATTTTAAATTTATTCCATAATAAAGCTCCTACCTGTAGAGGATCAACTATATTATTATTTCAGTTTTAATCAGAGAATTGTGTAAATAGTGCCTGG
+
@@CFFFFFHHGHHJJJJJJJJIJIIJIJJIHIGIGIIIHFGIIJIFFCHIGHIIGGIIJJJJJJJJJGHGIJJHGIIIJGJJJIECHFEECHF?@@EFEC
```

Here `NAGATC` is the index.

## index_stats

## split_single_reads
```
SYNOPSIS
    split_single_reads -i INDEX [-i INDEX2] INPUT1 [INPUT2] > OUTPUT.fastq

DESCRIPTION
    This program allows to select reads with certain indices from a FASTQ file where first line of entries look like:
    @HISEQ:31:C39VUACXX:4:1101:3194:1985 2:N:0:NAGATN and NAGATN is the index.

    -h, --help
          Displays this help message.
    -i, --index INDEX
          Index to select.
```
