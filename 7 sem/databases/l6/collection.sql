--SOURCE
CREATE TABLE collections.Source (
    id int generated always as identity,
    description varchar(128),
    CONSTRAINT source_pk PRIMARY KEY (id)
);

--COUNTRY
CREATE TABLE collections.Country (
    id int generated always as identity,
    name varchar(128) unique,
    CONSTRAINT country_pk PRIMARY KEY (id)
);
INSERT into collections.Country (name) values ('ВКЛ');

--AUTHOR
CREATE TABLE collections.Author (
    id int generated always as identity,
    name varchar(128) unique,
    CONSTRAINT author_pk PRIMARY KEY (id)
);


--COLLECTION
CREATE TABLE collections.Collection (
    id int generated always as identity,
    name varchar(128) unique,
    CONSTRAINT collection_pk PRIMARY KEY (id)
);

--THEME
-- DROP TABLE collections.Theme;
CREATE TABLE collections.Theme (
    id int generated always as identity,
    collection_id int,
    name varchar(128),
    CONSTRAINT theme_pk PRIMARY KEY (id),
    CONSTRAINT theme_collection_fk FOREIGN KEY (collection_id)
        REFERENCES collections.Collection(id) ON DELETE CASCADE
);

--SECTION
CREATE TABLE collections.Section (
    id int generated always as identity,
    theme_id int,
    name varchar(128),
    CONSTRAINT section_pk PRIMARY KEY (id),
    CONSTRAINT section_theme_fk FOREIGN KEY (theme_id)
        REFERENCES collections.Theme(id)
);


--ITEM
-- DROP TABLE collections.Item;
CREATE TABLE Item (
    id int generated always as identity,
    section_id int,
    source_id int,
    author_id int,
    country_name varchar(128) DEFAULT 'ВКЛ',

    name varchar(128),
    price decimal,
    origin_year varchar(4),
    obtain_date date,

    CONSTRAINT item_pk PRIMARY KEY (id),
    CONSTRAINT item_section_fk FOREIGN KEY (section_id)
        REFERENCES collections.Section(id),
    CONSTRAINT item_source_fk FOREIGN KEY (source_id)
        REFERENCES collections.Source(id),
    CONSTRAINT item_author_fk FOREIGN KEY (author_id)
        REFERENCES collections.Author(id),
    CONSTRAINT item_country_fk FOREIGN KEY (country_name)
        REFERENCES collections.Country(name),

    CONSTRAINT item_price CHECK (price >= 0.5 and price <= 10000)
);


--FOR TRADE OR SALE
DROP TABLE collections.For_Trade_Or_Sale;
CREATE TABLE collections.For_Trade_Or_Sale (
    id int generated always as identity,
    item_id int,
    owner_id int,

    price decimal,

    CONSTRAINT for_trade_or_sale_pk PRIMARY KEY (id),
    CONSTRAINT for_trade_or_sale_item_fk FOREIGN KEY (item_id)
        REFERENCES Item(id),
    CONSTRAINT for_trade_or_sale_owner_fk FOREIGN KEY (owner_id)
        REFERENCES collections.Owner(id)
);

--OWNER
CREATE TABLE collections.Owner (
    id int generated always as identity,

    name varchar(128),
    contacts varchar(128),

    CONSTRAINT owner_pk PRIMARY KEY (id)
);


--EXPOSITION PLACE
CREATE TABLE collections.Exposition_Place (
    id int generated always as identity,
    name varchar(128),
    CONSTRAINT exposition_place_pk PRIMARY KEY (id)
);
INSERT into collections.Exposition_Place (name) values ('Исторический Факультет БГУ');

--EXPOSITION
CREATE TABLE Exposition (
    id int generated always as identity,
    place int DEFAULT 1,

    name varchar(128),
    visitors_amount int,
    exposition_date date,

    CONSTRAINT exposition_pk PRIMARY KEY (id),
    CONSTRAINT exposition_place_fk FOREIGN KEY (place)
        REFERENCES collections.Exposition_Place(id),

    CONSTRAINT visitors_amount_check CHECK (visitors_amount < 300)
);

--EXPOSITION MTM
CREATE TABLE Exposition_MTM (
    id int generated always as identity,
    exposition int,
    item int,

    CONSTRAINT exposition_mtm_pk PRIMARY KEY (id),
    CONSTRAINT exposition_mtm_exposition_fk FOREIGN KEY (exposition)
        REFERENCES Exposition(id),
    CONSTRAINT exposition_mtm_item_fk FOREIGN KEY (item)
        REFERENCES Item(id)
);




