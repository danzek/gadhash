# Google Analytics domain hash rainbow tables

"Rainbow tables" of hashed domains are made available here using `gadhash` to compute the Google Analytics (GA) domain hashes. This will enable interested parties to query a domain hash to find the corresponding domain. 

The tables are in CSV (comma-delimited) format. The first column is the GA domain hash and the second is the domain. Lists are sorted by hash.

## Domain list sources

So far, the following list sources have been used. The date each was obtained is indicated in the file name for each rainbow table.

 - [Cisco Umbrella Popularity List : Top 1 million](http://s3-us-west-1.amazonaws.com/umbrella-static/index.html)

## Acknowledgements

Thanks to [Ryan Benson](https://github.com/obsidianforensics) for identifying that subdomains are included in GA domain hashes and for telling me about the Cisco Umbrella Popularity List.

I welcome contributions. Contact me at d@4n68r.com, create an issue, and/or fork this code and create a pull request.
 
## License and disclaimer

The Cisco Umbrella Popularity List is &copy; 2016 Cisco. The list was obtained from http://s3-us-west-1.amazonaws.com/umbrella-static/index.html

THE SOFTWARE AND RAINBOW TABLES ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE AND/OR RAINBOW TABLES OR THE USE OR OTHER DEALINGS IN THE SOFTWARE AND/OR RAINBOW TABLES.
