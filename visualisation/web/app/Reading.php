<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Reading extends Model
{

	protected $fillable = [
		'reading_time', 'value'
	];


	public function device()
    {
	    return $this->belongsTo('App\Device');
    }
}
