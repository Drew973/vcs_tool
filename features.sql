create table features(
        pk INTEGER PRIMARY KEY not null--huge bug in sqlite. primary key can all be null. Should autoincrement
        ,lane text
        ,s_ch float
        ,e_ch float
        ,width float
        ,feature text
        ,location text
        ,photo text
        ,section_label text
        ,foreign key(section_label) references sections(label) on update cascade)


--insert into features(lane,s_ch,e_ch,width,feature,location,photo,section_label,photo_number)
--select lane,s_ch,e_ch,width,feature,location,photo,(select label from sections where number=section_number),photo_number from f2