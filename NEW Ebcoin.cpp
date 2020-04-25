@extends('partials.layout_cp')

@push('title')
    {{ __('app.title') }} | {{ __('common.title') }}
@endpush

@push('script-head')
    <script type="text/javascript" src="https://momentjs.com/downloads/moment.min.js"></script>
    <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.24.0/moment-with-locales.min.js"></script>
    <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/moment-timezone/0.5.11/moment-timezone-with-data.js"></script>
@endpush

@section('content')
    <div class="container">
        <div class="row">
            <div class="col-md-12">
                <div class="title-header ">
                    <div class="min-menu row">
                        <div class="col-md-6"><div class="title">{{ __('common.title') }}</div></div>
                        <div class="col-md-6">
                            <div class="right-panel">
                                <a href="{{ route('manage.cp.block-chain.create', $property_id) }}" class="btn btn-normal btn-m m-r">{{ __('manage/cp/block-chain/block-chain.new_block_chain') }}</a>
                                <a href="{{ route('manage.cp.block-chain.video-compare.index', $property_id) }}" class="btn btn-normal btn-m m-r">{{ __('manage/cp/video-compare/compare.video_compare') }}</a>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="ibox">
                    <div class="ibox-content">
                        <div class="video-list spwp">
                            <table class="table table-hover">
                                <thead>
                                <tr>
                                    <th class="image"></th>
                                    <th class="video-name fx-video-name-dpp">{{ __('manage/cp/block-chain/block-chain.playlist') }}</th>
                                    <th width="10%">{{ __('manage/cp/block-chain/block-chain.evidence_count') }}</th>
                                    <th>{{ __('manage/cp/block-chain/block-chain.submitted_at') }}</th>
                                    <th>{{ __('manage/cp/block-chain/block-chain.last_updated') }}</th>
                                    <th>{{ __('common.status') }}</th>
                                    <th class="right" width="10%">{{ __('common.actions') }}</th>
                                </tr>
                                </thead>
                                <tbody>
                                @php
                                    $status = [
                                        \App\Models\PlaylistEvidenceRequest::STATUS_PROCESSING => 'label-grey',
                                        \App\Models\PlaylistEvidenceRequest::STATUS_DONE => 'label-active',
                                    ];
                                @endphp
                                @foreach( $playlist_evidences as $playlist_evidence)
                                    <tr>
                                        <td class="image">
                                            <div class="video-img">
                                                <img src="{{ App\Services\Serve\PlaylistImageService::getImageUrl($playlist_evidence->playlist, $property_id, null, 240) }}">
                                            </div>
                                        </td>
                                        <td class="video-name fx-video-name-dpp">
                                            <a href="{{ route('manage.cp.block-chain.edit', [$property_id, $playlist_evidence->id]) }}">{{ $playlist_evidence->playlist->name }}</a>
                                        </td>
                                        <td class="playlist-amount">
                                            <span class="amount">{{ $playlist_evidence->playlist->evidence_entries_count }}</span> <small>{{ __('manage/cp/block-chain/block-chain.available') }}</small>
                                        </td>
                                        <td class="date">
                                            <div id="{{ $playlist_evidence->id }}-{{ $playlist_evidence->created_at->timestamp }}"></div>
                                            <small class="timestamp" id="{{ $playlist_evidence->id }}" dt="{{ $playlist_evidence->created_at->timestamp }}"></small>
                                        </td>
                                        <td class="date">
                                            <div id="{{ $playlist_evidence->id }}-updated-{{ $playlist_evidence->updated_at->timestamp }}"></div>
                                            <small class="timestamp" id="{{ $playlist_evidence->id }}-updated" dt="{{ $playlist_evidence->updated_at->timestamp }}"></small>
                                        </td>
                                        <td><span class="label {{ $status[$playlist_evidence->status] }}">{{ __('manage/cp/block-chain/block-chain.'.$playlist_evidence->StatusDisplay()) }}</span></td>
                                        <td class="playlist-actions">
                                            @if ($playlist_evidence->status > \App\Models\PlaylistEvidenceRequest::STATUS_PROCESSING)
                                                <a href="{{ route('manage.cp.block-chain.edit', [$property_id, $playlist_evidence->id]) }}" class="btn btn-normal btn-m">{{ __('common.manage') }}</a>
                                            @elseif ($playlist_evidence->playlist->evidenceEntries->count()) 
                                                <a href="{{ route('manage.cp.block-chain.edit', [$property_id, $playlist_evidence->id]) }}" class="btn btn-normal btn-m">{{ __('common.manage') }}</a>
                                            @endif
                                        </td>
                                    </tr>
                                @endforeach
                                </tbody>
                            </table>
                            <div class="row">
                                <div class="col-sm-5">
                                    <div class="dataTables_info">
                                        @if ($playlist_evidences->count()>0)
                                            {{
                                                __(
                                                    'manage/cp/block-chain/block-chain.showing_from_to_evidences',
                                                    [
                                                        'from'=>$playlist_evidences->firstItem(),
                                                        'to'=>$playlist_evidences->lastItem(),
                                                        'total'=>$playlist_evidences->total()
                                                    ]
                                                )
                                            }}
                                        @else
                                            {{ __('manage/cp/block-chain/block-chain.no_evidence') }}
                                        @endif
                                    </div>
                                </div>

                                <div class="col-sm-7">
                                    <div class="dataTables_paginate paging_simple_numbers">
                                        {{ $playlist_evidences->appends(request()->input())->links() }}
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
@stop

@push('js')
<script type="text/javascript" src="{{ asset('/js/format_timezones.js') }}"></script>
@endpush
