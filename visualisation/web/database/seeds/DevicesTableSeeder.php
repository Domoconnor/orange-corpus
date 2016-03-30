<?php

use Illuminate\Database\Seeder;

class DevicesTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('devices')->insert([
           'name' => str_random(10),
            'battery' => "67"
        ]);
    }
}
