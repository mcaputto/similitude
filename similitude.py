import argparse
import io
import subprocess

import pandas as pd


def main():
    # Build the command line interface
    parser = argparse.ArgumentParser(description='Compare strings in two files')
    parser.add_argument("source_file",
        help="source file containing strings separated by newlines",
        type=str,
        )
    parser.add_argument("target_file",
        help="target file containing strings separated by newlines",
        type=str,
        )
    args = parser.parse_args()

    # Compute the edit distances
    similitude = subprocess.run(
        ['./bin/similitude', args.source_file, args.target_file, "/dev/null",],
        stdout=subprocess.PIPE)

    # Load the data into pandas
    exported_distances = similitude.stdout.decode('utf-8')
    imported_distances = io.StringIO(exported_distances)
    df = pd.read_csv(
        imported_distances,
        sep=",",
        header=None,
        names=['source', 'target', 'distance'],
        )
    pd.set_option('display.width', 180)

    # Show a pivot table
    pt = pd.pivot_table(df, index=['source', 'target'])
    print(f'Pivot table:\n{pt}')
    
    # Show exact matches
    # exact_matches = df.loc[df['distance'] == 0]
    # print(exact_matches)
    
    # Show close matches
    # potential_matches = df.loc[df['distance'] < 3]
    # print(potential_matches)


if __name__ == '__main__':
    main()
