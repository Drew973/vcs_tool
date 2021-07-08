create table if not exists sections
(
            number int
            ,project text
            ,direction text
            ,job_no text
            ,date text
            ,client text
            ,contractor text
            ,label text primary key not null
            ,surveyor text
            ,weather text
            ,start_lon float
            ,start_lat float
            ,end_lon float
            ,end_lat float
            ,length_surveyed float
)



insert into sections
select * from sections_backup